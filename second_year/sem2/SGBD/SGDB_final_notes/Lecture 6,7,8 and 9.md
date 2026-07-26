# Query Optimization & Relational Operators

## 1. What is Query Optimization?

When you write a SQL query, there are often many different ways the database could execute it. Query optimization is the process of **finding the most efficient way**.

The optimizer sits between the SQL query you write and the actual execution:

```
SQL Query  →  Parser  →  Optimizer  →  Execution Plan  →  Result
                              ↑
                       System Catalog
                    (table sizes, indexes, etc.)
```

The optimizer:

- Looks at multiple possible plans
- Estimates the cost of each
- Picks the cheapest one

**What does "cost" mean?** Mostly disk access — reading and writing pages to/from disk is **much** slower than working in memory (RAM), so we try to minimize that.

---

## 2. Relational Operators

Every SQL query is internally translated into a combination of relational algebra operators. Each operator can be implemented using multiple algorithms, and that's where optimization choices come in.

|Operator|Symbol|What it does|
|---|---|---|
|Selection|σ|Filters rows by a condition (like WHERE)|
|Projection|π|Keeps only certain columns (like SELECT)|
|Join|⨝|Combines two tables based on a condition|
|Cross-product|×|Every row from table A paired with every row from table B|
|Union|∪|All rows from both tables (no duplicates)|
|Intersection|∩|Only rows that appear in both tables|
|Difference|−|Rows in table A that are not in table B|
|Grouping/Aggregation|γ|GROUP BY, COUNT, SUM, AVG, MIN, MAX|

The key insight: **operators return relations**, so they can be chained. The optimizer decides both which algorithm to use for each operator, and in what order to apply them.

---

## 3. Cost Model

### The Running Example

Throughout these lectures, the same database schema is used:

- **Students** (SID, SName, Age) — 500 pages, 80 records/page
- **Courses** (CID, CName, Description) — 100 pages, 80 records/page
- **Exams** (SID, CID, EDate, Grade, FacultyMember) — 1000 pages, 100 records/page

### Key Symbols

|Symbol|Meaning|
|---|---|
|M|Number of pages in the outer relation E|
|N|Number of pages in the inner relation S|
|B|Number of buffer pages available in RAM|
|pE|Records per page in E|
|pS|Records per page in S|

### Why Do We Count I/Os?

A disk read/write (I/O) is orders of magnitude slower than a RAM operation. When we say an operation costs "500 I/Os", we mean the system must read or write 500 pages to/from disk.

**Every page that is read costs 1 I/O. Every page that is written costs 1 I/O.**

### Buffer Pages

The database uses a **buffer pool** — a chunk of RAM that temporarily holds disk pages. Think of it as a working area:

```
DISK                          RAM (Buffer Pool)
┌────────────────┐            ┌──────────────────────────────────┐
│  Exams table   │ ←── read → │  Buffer page 1  │  Buffer page 2 │
│  Students table│            │  Buffer page 3  │  Output buffer │
│  Indexes...    │ ← write ── │                 │                │
└────────────────┘            └──────────────────────────────────┘
```

More buffer pages = less re-reading from disk = better performance.

---

## 4. Access Paths and Indexes

### What is an Access Path?

An **access path** is the method used to retrieve tuples from a relation. There are two basic kinds:

1. **File scan** — read every single page of the table from start to end
2. **Index access** — use an index to jump directly to the relevant data

If a relation has an index that matches your query condition, you have at least two access paths to choose from.

### Types of Indexes

#### B+ Tree Index

- Stores entries in sorted order
- Works for equality (`=`) and **range** queries (`<`, `>`, `<=`, `>=`, `<>`)
- The search key can be a prefix of multiple attributes

#### Hash Index

- Uses a hash function to map a key to a bucket
- Works **only** for equality queries (`=`)
- Cannot help with ranges — hashing destroys ordering

|Feature|B+ Tree Index|Hash Index|
|---|---|---|
|Equality (`=`)|✅ Yes|✅ Yes|
|Range (`<`, `>`, etc.)|✅ Yes|❌ No|
|Ordered traversal|✅ Yes|❌ No|

### When Does a Condition Match an Index?

This is very important for understanding when the optimizer will use an index.

**For a Hash Index:** The condition must provide an exact value for **every** attribute in the search key.

|Condition|Hash index on `<a, b, c>`|Matches?|
|---|---|---|
|`a = 10 AND b = 5 AND c = 2`|Full key provided|✅ Yes|
|`a = 10 AND b = 5`|Missing c|❌ No|
|`b = 5`|Missing a and c|❌ No|
|`a = 10`|Missing b and c|❌ No|

**For a B+ Tree Index:** The condition must cover a **prefix** of the search key (you can skip the end, but not the beginning).

|Condition|B+ Tree index on `<a, b, c>`|Matches?|
|---|---|---|
|`a = 10 AND b = 5 AND c = 2`|Prefix: all 3|✅ Yes|
|`a = 10 AND b = 5`|Prefix: first 2|✅ Yes|
|`a = 10`|Prefix: first 1|✅ Yes|
|`b = 5`|Skips `a` — not a prefix|❌ No|
|`b = 5 AND c = 2`|Skips `a` — not a prefix|❌ No|

### Clustered vs. Unclustered Index

This distinction dramatically affects performance.

**Clustered Index:** The actual data rows on disk are physically stored in the same order as the index. When you retrieve 100 matching records, they are likely on just a few consecutive pages.

**Unclustered Index:** The index and the data are stored independently. Matching records are scattered across many different pages. In the worst case, each matching record could be on a different page — meaning 1 I/O per record.

**Example:** Suppose a query returns 10,000 matching records from the Exams table (1,000 pages total).

|Access Method|Cost|
|---|---|
|Clustered B+ tree index|~100 I/Os (data is contiguous)|
|Unclustered B+ tree index|Up to 10,000 I/Os (worst case: one I/O per record)|
|Full file scan|1,000 I/Os (always reads everything)|

For range queries on large result sets, an unclustered index can actually be **worse** than a full scan.

### Selectivity

The **selectivity** of an access path is how many pages it retrieves. A more selective path retrieves fewer pages.

```
Full file scan:     1000 pages retrieved  (low selectivity)
Matching index:        3 pages retrieved  (high selectivity) ← prefer this
```

The optimizer always tries to use the **most selective** access path available.

---

## 5. Selection Operations

Selection (σ) filters rows based on a condition.

```sql
SELECT * FROM Exams WHERE FacultyMember = 'Ionescu';
```

### Case 1: No Index, No Sorting

Must do a **full file scan** — read every page and check every tuple.

**Cost: M I/Os** (1,000 for Exams)

### Case 2: No Index, but Table is Sorted on the Attribute

Use **binary search** to find the first matching tuple, then scan sequentially from there.

**Cost:** O(log₂ M) for the binary search + scan cost depending on result size

Binary search on Exams: log₂(1000) ≈ 10 I/Os to find the starting point.

### Case 3: B+ Tree Index on the Attribute

The optimizer uses the index to navigate directly to relevant records:

1. **Traverse the tree** from root to the first matching leaf — typically 2–4 I/Os
2. **Scan leaf pages** to get all qualifying entries
3. **Fetch corresponding records** — cost depends on whether the index is clustered

|Index type|Query: `FacultyMember < 'C%'` (returns ~10,000 tuples)|
|---|---|
|Clustered B+ tree|~100 I/Os|
|Unclustered B+ tree|Up to 10,000 I/Os|
|Full file scan|1,000 I/Os|

> In this case, the unclustered index is actually the **worst** option. The optimizer knows this and might prefer a full scan.

### General Selection Conditions (AND / OR)

Conditions can be expressed in **Conjunctive Normal Form (CNF)** — a collection of conjuncts joined by AND, where each conjunct may contain OR.

```
Original:   (EDate < '4-1-2021' AND Grade = 10) OR CID = 5 OR SID = 3

CNF form:   (EDate < '4-1-2021' OR CID = 5 OR SID = 3)
         AND (Grade = 10 OR CID = 5 OR SID = 3)
```

**Evaluation strategies:**

**Strategy 1 — Use the most selective access path:**

- Use the best matching index
- For each retrieved tuple, check the remaining conditions

**Strategy 2 — Use multiple indexes (AND conditions):**

- Use index A to get a set of row IDs (rids) matching condition A
- Use index B to get a set of row IDs matching condition B
- Intersect the two sets → fetch only those rows → apply remaining conditions

**Strategy 3 — Handle OR with indexes:**

- If every term in an OR-condition has a matching index: use each index, then take the **union** of the results
- If any term in an OR-condition has no index: must do a full file scan anyway

---

## 6. Sorting Algorithms

Sorting is used internally for ORDER BY, DISTINCT, GROUP BY, joins, and set operations.

If the data fits entirely in RAM, any in-memory algorithm (like QuickSort) works. The interesting case is when data doesn't fit — that's where **external sorting** comes in.

---

### 6.1 Simple Two-Way Merge Sort

Uses exactly **3 buffer pages** (2 input, 1 output). Works in multiple passes over the data.

#### Pass 0 — Create initial sorted runs

Read each page one at a time, sort it in memory, write it back. After Pass 0, you have N runs that are each 1 page long.

**Example with 7 pages (each page holds 2 records for simplicity):**

```
Input:   [3,4] [6,2] [9,4] [8,7] [5,6] [3,1] [2]

After Pass 0 (sort each page individually):
         [3,4] [2,6] [4,9] [7,8] [5,6] [1,3] [2]
```

#### Pass 1, 2, ... — Merge pairs of runs

Take two adjacent runs, merge them into one sorted run of double the size. Each pass doubles the run length.

```
Pass 0 → 7 runs of length 1
Pass 1 → 4 runs of length 2  (last one may be shorter)
Pass 2 → 2 runs of length 4
Pass 3 → 1 run of length 7  ← fully sorted!
```

#### How the merge step works (using 3 buffers):

```
Buffer 1: [2, 6]  ← from run A
Buffer 2: [3, 4]  ← from run B
           ↓
Compare front elements: 2 < 3, so output 2
           ↓
Output buffer: [2, ...]  → write to disk when full
```

#### Cost of Two-Way Merge Sort

- Number of passes: **log₂(N) + 1**
- Each pass reads and writes every page once = 2 I/Os per page per pass
- **Total cost: 2 × N × (log₂(N) + 1) I/Os**

For N = 7 pages: 2 × 7 × (⌈log₂(7)⌉ + 1) = 2 × 7 × 4 = **56 I/Os**

#### The Problem

Two-Way Merge Sort only uses 3 buffers no matter how many are available. If you have 100 buffer pages, it still only uses 3 — a massive waste. This leads to many unnecessary passes.

---

### 6.2 External Merge Sort (the proper version)

This is the improvement — it uses **all B available buffer pages**.

#### Pass 0 — Create larger initial runs

Instead of sorting one page at a time, read **B pages** at once, sort them all in memory, and write out a run of B pages.

Number of initial runs: **⌈N / B⌉**

**Example: N = 108 pages, B = 5 buffer pages**

```
Pass 0: Read 5 pages → sort → write 5-page run
        Repeat → 22 runs total (21 of length 5, 1 of length 3)
```

#### Pass 1, 2, ... — B-1 way merge

Use B-1 buffers for input and 1 buffer for output. This means you can merge **B-1 runs at once** — far better than merging pairs!

```
Input buffer 1  ──┐
Input buffer 2  ──┤
Input buffer 3  ──┼──→  Merge logic  ──→  Output buffer → disk
Input buffer 4  ──┘
(4 input buffers when B=5)
```

Each merge pass reduces the number of runs by a factor of (B-1).

**Continuing the example (B=5, N=108):**

```
Pass 0: 22 runs (each ~5 pages)
Pass 1: merge 4 runs at a time → 6 runs (each ~20 pages)
Pass 2: merge 4 runs at a time → 2 runs (80 and 28 pages)
Pass 3: merge 2 remaining runs → 1 fully sorted run
```

#### Cost of External Merge Sort

- Number of passes: **⌈log(B-1)(N/B)⌉ + 1**
- **Total cost: 2 × N × number_of_passes I/Os**

For N=108, B=5: 2 × 108 × 4 = **864 I/Os**

#### Why External Merge Sort is Much Better

|N (pages)|B = 3 (two-way)|B = 5|B = 9|B = 17|B = 129|
|---|---|---|---|---|---|
|100|7 passes|4 passes|3 passes|2 passes|1 pass|
|1,000|10 passes|5 passes|4 passes|3 passes|2 passes|
|10,000|13 passes|7 passes|5 passes|4 passes|2 passes|
|100,000|17 passes|9 passes|6 passes|5 passes|3 passes|

More buffer pages → fewer passes → dramatically lower cost. With B=129, even 10,000 pages can be sorted in just 2 passes.

---

## 7. Join Algorithms

Joins are the most expensive and most important operations to optimize. For a join `Exams ⨝ Students` on SID:

- Exams (E): 1000 pages, 100 records/page → M = 1000, pE = 100
- Students (S): 500 pages, 80 records/page → N = 500, pS = 80

---

### 7.1 Simple Nested Loops Join

The most naive approach. For every tuple in E, scan every tuple in S.

```
for each tuple e in Exams:
    for each tuple s in Students:
        if e.SID == s.SID:
            output <e, s>
```

**Cost: M + (pE × M × N) = 1000 + (100 × 1000 × 500) = 50,001,000 I/Os**

This is catastrophically expensive. Never use this in practice.

---

### 7.2 Page-Oriented Nested Loops Join

A simple improvement: loop over **pages** instead of **tuples**. For each page in E, scan all pages in S, and match tuples.

```
for each page pe in Exams:
    for each page ps in Students:
        for each pair (e, s) where e.SID == s.SID:
            output <e, s>
```

**Cost: M + (M × N) = 1000 + (1000 × 500) = 501,000 I/Os**

Better, but still expensive. Tip: the **smaller** relation should be the outer loop. With S as outer: 500 + 500×1000 = 500,500 I/Os.

---

### 7.3 Block Nested Loops Join (BNLJ)

The key insight: don't read S once per page of E — read a whole **block** of E pages into memory, then scan S once for that entire block.

```
for each block of pages from E (fitting in memory):
    for each page ps in S:
        match all e tuples in the block against all s tuples in ps
```

```
RAM (B pages):
┌───────────────────────────────┬───────────────┬───────────┐
│   Block from E (B-2 pages)   │  1 page of S  │  Output  │
└───────────────────────────────┴───────────────┴───────────┘
```

**Cost formula:**

```
Cost = M + ⌈M / block_size⌉ × N
```

**Example: B = 102 pages, block size = 100 pages (leaving 1 for S input, 1 for output)**

```
Outer = Exams (E), block size = 100
Number of blocks = ⌈1000 / 100⌉ = 10
Cost = 1000 + 10 × 500 = 6,000 I/Os
```

**Example: Outer = Students (S), block size = 100**

```
Number of blocks = ⌈500 / 100⌉ = 5
Cost = 500 + 5 × 1000 = 5,500 I/Os
```

> **Optimization:** Build an in-memory hash table for the E block instead of scanning it linearly. This reduces CPU cost but doesn't change I/O count.

The bigger the block (i.e., the more RAM available), the fewer times S needs to be scanned.

---

### 7.4 Index Nested Loops Join

If the **inner relation** has an index on the join column, use it!

```
for each tuple e in Exams:
    use index on Students.SID to find matching Students tuples
    output <e, s> for each match
```

**Cost: M + (pE × M) × cost_per_lookup**

For each of the (pE × M) = 100,000 exam records, the cost per lookup depends on the index type:

|Index on Students.SID|Lookup cost|
|---|---|
|Hash index (clustered)|~1.2 I/Os per lookup (index lookup) + 1 I/O (fetch record)|
|B+ tree index|2–4 I/Os to traverse tree + fetch cost|
|Unclustered index|Up to 1 I/O per matching tuple in S|

**Example: hash index on Students.SID (clustered)**

```
Scan Exams:                   1,000 I/Os
Per exam record:
  - hash index lookup:         1.2 I/Os
  - fetch matching Student:    1.0 I/O
  Total per record:            2.2 I/Os × 100,000 records = 220,000 I/Os
─────────────────────────────────────────────────────────
Total:                       221,000 I/Os
```

This is worse than BNLJ! But if few records match (high selectivity), it can be much better.

---

### 7.5 Sort-Merge Join

Works by first sorting both relations on the join column, then merging them.

**Step 1:** Sort Exams on SID. Sort Students on SID.

**Step 2:** Scan both sorted relations simultaneously. Since they're sorted, matching tuples are grouped into **partitions** (groups with the same SID value).

```
Sorted Exams (by SID):   ... SID=30, SID=30, SID=45, SID=45, SID=45, SID=50 ...
Sorted Students (by SID):... SID=30, SID=45, SID=50 ...
                                 ↕           ↕           ↕
                              match       match       match
```

The merge scans E once. For S, each partition is scanned as many times as there are matching tuples in E's corresponding partition. In most cases (no many-to-many explosion), this is efficient.

**Cost:**

- Sort Exams: ~4,000 I/Os (2 passes × 2 × 1,000)
- Sort Students: ~2,000 I/Os (2 passes × 2 × 500)
- Merge phase: M + N = 1,000 + 500 = 1,500 I/Os
- **Total: ~7,500 I/Os**

---

### 7.6 Hash Join

The most commonly used join algorithm for equality joins. Works in two phases.

#### Partitioning Phase

Use a hash function `h` to partition **both** relations into B-1 buckets based on the join column:

```
For each exam tuple e:    compute h(e.SID) → assign to partition E₁, E₂, ... E_{B-1}
For each student tuple s: compute h(s.SID) → assign to partition S₁, S₂, ... S_{B-1}
```

The key guarantee: if `e.SID == s.SID`, then `h(e.SID) == h(s.SID)` — so matching tuples always land in **the same partition number**. Tuple in E₃ can only match with tuples in S₃.

```
DISK                        RAM                         DISK
Exams  →  [input page]  →  hash fn  →  [E₁ output]  →  partition E₁
                                    →  [E₂ output]  →  partition E₂
                                    →  [E₃ output]  →  partition E₃
```

Cost of partitioning: read both relations once, write them once = **2 × (M + N) I/Os**

#### Probing Phase

For each partition Eₖ:

1. Read Eₖ into memory, build an in-memory hash table (using a different hash function `h₂`)
2. Read Sₖ one page at a time, probe the hash table for matches
3. Output matching pairs

```
For each partition k:
  Load Eₖ into memory hash table
  For each page of Sₖ:
    For each tuple s in that page:
      Look up h₂(s.SID) in hash table
      Output matches
```

Cost of probing: read all partitions once = **M + N I/Os**

**Total Hash Join Cost: 2(M+N) + (M+N) = 3(M+N)**

For our example: 3 × (1,000 + 500) = **4,500 I/Os**

**Memory requirement:** Each partition of E must fit in RAM during probing. Approximately: **B > √M**

---

### Join Algorithm Comparison

|Algorithm|Cost (Exams ⨝ Students)|Notes|
|---|---|---|
|Simple Nested Loops|~50,000,000 I/Os|Never practical|
|Page-Oriented NL|~501,000 I/Os|Simple but slow|
|Block Nested Loops|~5,500 – 6,000 I/Os|Good with enough memory|
|Index Nested Loops|Varies widely|Best when index exists + few matches|
|Sort-Merge Join|~7,500 I/Os|Good for sorted data|
|Hash Join|~4,500 I/Os|Usually fastest for equality joins|

---

## 8. Projection and Set Operations

### Projection

Projection (π) eliminates unwanted columns and removes duplicates (for `SELECT DISTINCT`).

```sql
SELECT DISTINCT E.SID, E.CID FROM Exams E;
```

The main cost is **duplicate elimination**, which requires either sorting or hashing.

#### Sorting-Based Projection

1. **Scan** Exams, keeping only SID and CID → write temporary relation E' (250 pages, since tuples shrink from 40 bytes to 10 bytes)
2. **Sort** E' on all columns
3. **Scan** sorted E' and remove consecutive duplicates

**Cost (20 buffer pages):** 1,000 + 250 + 1,000 + 250 = **2,500 I/Os**

**Improvement:** Integrate projection into the sort's Pass 0 — drop unwanted columns while building initial runs. This reduces the size of data being written and merged.

**Improved cost:** 1,000 + 250 + 250 = **1,500 I/Os** (only 2 passes instead of 3 steps)

#### Hashing-Based Projection

1. **Partitioning:** Read E, discard unwanted columns, hash the remaining columns → B-1 partitions. Tuples in different partitions cannot be duplicates.
2. **Duplicate elimination:** For each partition, read it into memory and build a hash table — remove any tuple that already exists.

**Cost: M + 2T** where T is the size of the projected relation

For Exams: 1,000 + 2×250 = **1,500 I/Os** — same as the improved sorting approach.

### Set Operations

|Operation|Implementation approach|
|---|---|
|Intersection|Like a join with equality on all columns|
|Cross-product|Like a join with no condition|
|Union|Sort both on all attributes, scan in parallel eliminating duplicates (or use hashing)|
|Set-difference|Adapt the merge or hash approach to exclude shared tuples|

### Aggregate Operations

- **Without GROUP BY:** Simply scan the relation and keep a running total (for SUM, COUNT, AVG, MIN, MAX). Cost: M I/Os.
- **With GROUP BY:** Sort (or hash) the relation on the grouping attributes, then scan and compute aggregates for each group.
- **Using an index:** If a tree index covers all required attributes and the GROUP BY columns form a prefix of the search key, data arrives pre-sorted — no explicit sort needed.

---

## 9. Query Evaluation Plans

A **query evaluation plan** is a fully specified tree of relational operators, annotated with the implementation method chosen for each operation.

### Example

```sql
SELECT S.SName
FROM Exams E, Students S
WHERE E.SID = S.SID AND E.CID = 7 AND S.Age > 23;
```

**A basic plan (expensive):**

```
        π SName  (on-the-fly)
            |
     σ CID=7 ∧ Age>23  (on-the-fly)
            |
  Exams ⨝ Students  (Page-Oriented Nested Loops)
  (file scan)  (file scan)
```

Cost: 1,000 + 1,000 × 500 = **501,000 I/Os**

### Pipelined vs. Materialized Evaluation

**Materialization:** An intermediate result is written to disk, then read again by the next operator. Costly in I/Os.

**Pipelining (on-the-fly):** Each tuple produced by operator A is immediately passed to operator B — no writing to disk. Saves reading and writing the intermediate result entirely.

Most plans use pipelining wherever possible. Only algorithms that need to see all input before producing output (like sort, or build phase of hash join) break the pipeline.

### Query Blocks

The optimizer handles **one query block at a time**. A query block is a simple SQL query without nesting — exactly one SELECT and one FROM clause.

Nested queries are broken into separate blocks, optimized independently, and then combined.

```sql
SELECT S.SID, MIN(E.EDate)
FROM Students S, Exams E, Courses C
WHERE ... AND S.Age = (SELECT MAX(S2.Age) FROM Students S2)
GROUP BY S.SID
HAVING COUNT(*) > 2;
```

This becomes two blocks: the nested `SELECT MAX(...)` and the outer query. The optimizer processes the inner block first, substitutes its result, then optimizes the outer block.

---

## 10. Optimization Strategies

### Core Idea: Reduce Data Early

The later you filter data, the more work you've done on rows that won't appear in the final result. The optimizer tries to apply filters as early as possible.

### Strategy 1: Push Selections Ahead of Joins

**Before optimization:**

```
Join Exams and Students (huge)
→ Then filter CID=7 and Age>20
```

**After optimization:**

```
Filter Exams: keep only CID=7  → small result T1
Filter Students: keep only Age>20 → smaller result T2
→ Then join T1 and T2
```

**Impact on the motivating example (5 buffer pages):**

|Plan|Cost|
|---|---|
|Naive (join first, then filter)|501,000 I/Os|
|Push selections, use Sort-Merge Join|4,060 I/Os|
|Push selections, use Block NL Join|2,770 I/Os|
|Push projections too (drop unneeded columns)|~2,000 I/Os|
|Use indexes (hash on CID, hash on SID)|1,210 I/Os|

### Strategy 2: Push Projections Ahead of Joins

Drop columns you don't need before joining, so the intermediate relations are smaller. Fewer columns = fewer pages = less I/O.

### Strategy 3: Use Indexes

When an index exists on the join column or selection column, use it to avoid full scans. The most dramatic gains come from combining a clustered index with pipelining (no materialization of intermediate results).

**Best case from the example — using indexes:**

```
σ CID=7 (use hash index on CID)  → 10 I/Os, result pipelined directly into join
⨝ SID=SID (Index Nested Loops, use hash index on SID)
σ Age>20 + π SName (on-the-fly)

Total: 10 + 1,000 × 1.2 = 1,210 I/Os
```

### Strategy 4: Choose the Right Join Algorithm

No single join algorithm is always best. The choice depends on:

- Size of the relations
- Available buffer pages
- Existing indexes
- Whether data is already sorted

|Situation|Preferred algorithm|
|---|---|
|One relation fits in memory|Block Nested Loops|
|Index on join column of inner relation|Index Nested Loops|
|Both relations are large, no indexes|Hash Join|
|Data is already sorted|Sort-Merge Join|
|Inequality join condition|Sort-Merge or Nested Loops (hash/sort-merge don't work for inequalities)|

### Strategy 5: Choose the Smaller Relation as Outer

For nested loops joins, the inner relation is scanned repeatedly. Making the inner relation the smaller one reduces total scans.

---

## Quick Reference: Key Formulas

| Operation                         | Cost Formula                             |
| --------------------------------- | ---------------------------------------- |
| File scan                         | M I/Os                                   |
| Two-Way Merge Sort                | 2 × N × (⌈log₂ N⌉ + 1) I/Os              |
| External Merge Sort               | 2 × N × (⌈log(B-1)(N/B)⌉ + 1) I/Os       |
| Simple Nested Loops Join          | M + pE × M × N                           |
| Page-Oriented NL Join             | M + M × N                                |
| Block NL Join                     | M + ⌈M/block_size⌉ × N                   |
| Index NL Join                     | M + pE × M × (index_lookup + fetch_cost) |
| Sort-Merge Join                   | Sort(E) + Sort(S) + M + N                |
| Hash Join                         | 3 × (M + N)                              |
| Projection (sort-based, improved) | M + 2T                                   |
| Projection (hash-based)           | M + 2T                                   |

Where T = size of the projected (smaller) relation.

---

_End of guide — based on Lecture notes 6, 7, and 8 from the Database Management Systems course._



