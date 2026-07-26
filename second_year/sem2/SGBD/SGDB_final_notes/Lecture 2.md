# Transactions. Concurrency control

### 1.Conflict

#### • C – set of transactions
#### • Sch(C) – the set of schedules for C
#### • Op(C) – set of operations of the transactions in C

#### • consider schedule S ∈ Sch(C)
#### • the conflict relation of S is defined as: 
	 conflict(S) = {(op1 , op2 ) | op1 , op2 ∈ Op(C), op1 occurs before op2 in S, op1 and op2 are in conflict}

---

### 2. Conflict Serializability

#### S1 and S2 are conflict equivalent (S1 ≡𝑐 S2) if conflict(S1) = conflict(S2), i.e.:
	• S1 and S2 contain the same operations of the same transactions
	• every pair of conflicting operations is ordered in the same manner in S1 and S2

![[Pasted image 20260528163651.png]]

### How to find conflicts??
#### A conflict happens when Ti and Tj operate on the same data, and at least one of the operations is a write (ex: Ri(A), Wj(A)).
#### The way to find them intuitively is to look at a read/write operation in one transaction, then look at it's "opposite" operation on the other transaction (read -> look at write, write -> look at write OR read). If you find 2 operations in 2 different transactions that operate on the same data and at least one is a write => conflict.

Precedence Graph:
- #### one node for every committed transaction in S
- #### an arc from Ti to Tj if an action in Ti precedes and conflicts with one of the actions in Tj

Theorem: 
- #### a schedule S ∈ Sch(C) is conflict serializable if and only if its precedence graph is acyclic
![[Pasted image 20260528163834.png]]

 Algorithm to test the conflict serializability of a schedule S ∈ Sch(C):
 
    1. create a node labeled Ti in the precedence graph for every committed transaction Ti in the schedule
  
	2. create an arc (Ti ,Tj ) in the precedence graph if Tj executes a Read(A) after a Write(A) executed by Ti
  
	  3. create an arc (Ti ,Tj ) in the precedence graph if Tj executes a Write(A) after a Read(A) executed by Ti
  
	  4. create an arc (Ti ,Tj ) in the precedence graph if Tj executes a Write(A) after a Write(A) executed by Ti
  
	  5. S is conflict serializable if and only if the resulting precedence graph has no cycles

---

## 3. View Serializability

#### A more general, sufficient condition for serializability 

Let Ti , Tj ∈ C, S1, S2 ∈ Sch(C); S1 and S2 are view equivalent, written S1 ≡𝑣 S2 , if the following conditions are met:

	 - if Ti reads the initial value of V in S1 , then Ti also reads the initial value of V in S2
	 - if Ti reads the value of V written by Tj in S1 , then Ti also reads the value of V written by Tj in S2 ;
	 - if Ti writes the final value of V in S1 , then Ti also writes the final value of V in S2.
	 
i.e.: each transaction performs the same computation in S1 and S2 and S1 and S2 produce the same final database state.

![[Pasted image 20260529123344.png]]
![[Pasted image 20260529123356.png]]
- #### not equivalent because they do not produce the same output!
- #### S1 does A -= 100 first, but S3 does A  * = 0.2 first, which will produce a different output because (A - 100) * 0.2 != A * 0.2 - 100. The same goes for B, but it's enough to know that A is not the same at the end.

A schedule S ∈ Sch(C) is view serializable if there exists a serial schedule S0 ∈ Sch(C) such that S ≡𝑣 S0 , i.e., S is view equivalent to some serial schedule.

![[Pasted image 20260529123736.png]]

---

## 4. Lock-Based Concurrency Control

- ### technique used to guarantee serializable, recoverable schedules
- lock:
	 - #### a tool used by the transaction manager to control concurrent access to data
	 - #### prevents a transaction from accessing a data object while another transaction is accessing the object

 ___SLock (shared / read lock)___
 - #### if a transaction holds an SLock on an object, it can read the object, but it cannot modify it


___XLock (exclusive / write lock)___
- #### if a transaction holds an XLock on an object, it can both read and write the object

#### If a transaction holds an SLock on an object, other transactions can be granted SLocks on the object, but they cannot acquire XLocks on it.
#### If a transaction holds an XLock on an object, other transactions cannot be granted either SLocks or XLocks on the object.

|           | Shared | Exclusive |
| --------- | ------ | --------- |
| Shared    | Yes    | No        |
| Exclusive | No     | No        |


