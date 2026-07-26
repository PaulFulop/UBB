## Distributed Databases

* distributed systems
	* #### the data is stored at several sites
	* #### each site is managed by a DBMS that can run independently; these autonomous components can also be heterogeneous

### There's are some problems involving distributed systems, such as the fact that communication costs are bigger.
### Ex: accessing relations at remote sites => someone wants to access some data that can only be accesses via a relation stored in some other site => communication cost increase => slow.

The costs can be reduced via fragmentation / replication:

### Fragmentation:

 - #### a relation can be partitioned into fragments, which are stored across several sites (a fragment is kept where it’s most often accessed)
	 * #### example:
		 * #### partition the Employees relation into fragments PretoriaEmployees, SkopjeEmployees, etc.
		 * #### store fragment PretoriaEmployees in Pretoria, fragment SkopjeEmployees in Skopje, etc.

- #### break a relation into smaller relations (fragments); store the fragments instead of the relation itself
- #### horizontal (fragment of rows, reconstructing with union)
- ![[Pasted image 20260530163656.png]]
- vertical (subset of columns, performed using projection operators, reconstructed usin gnatural join)
- ![[Pasted image 20260530163757.png]]
- hybrid (horizontal fragmentation + vertical fragmentation)
- ![[Pasted image 20260530163842.png]]



### Replication:

- #### a relation can be replicated at each site where it's needed the most
	- #### example:
		- #### suppose the Employees relation is frequently needed in Beijing, New York, and Bucharest 
		- #### Employees can be replicated at the Bucharest site, the New York one, and in Beijing
- #### store multiple copies of a relation or of a relation fragment
- #### an entire relation or one or several fragments of a relation can be replicated at one or several sites

### Updating Distributed Data - Synchronous Replication 

2 techniques

1. Voting
	 • to modify object O, a transaction T1 must write a majority of its copies
	 • when reading O, a transaction T2 must read enough copies to make sure it's seeing at least one current copy
	 • e.g., O has 10 copies; T1 changes O: suppose T1 writes 7 copies of O; T2 reads O: it should read at least 4 copies to make sure one of them is current
	 • each copy has a version number (the copy that is current has the highest version number)
	 • not an attractive approach in most cases, because reads are usually much more common than writes (and reads are expensive in this approach)

2. Read-Any Write-All
	• transaction T1 modifies O: T1 must write all copies of O
	• transaction T2 reads O: T2 can read any copy of O (no matter which copy T2 reads, it will see current data, as T1 wrote all copies of O)
	• fast reads (only one copy is read), slower writes (compared with the voting technique)
	• most common approach to synchronous replication

#### So basically: voting -> a transaction must write the majority of an object's copies if that object has been updated in that transaction (not so logical and good), read-any write-all -> a transaction must write all of an object's copies (now every site holds the most current copy of that object => everything good)

### Updating Distributed Data - Asynchronous Replication 

2 approaches

1. primary site replication

2. peer-to-peer replication

difference: number of updatable copies (master copies)

### Lecture 12 is about:
- distributed deadlock
- distributed recovery -> two phase commit protocol


# Security

#### Protecting the data against unauthorized users.


### Bell and La Padula rules:
- #### user x can retrieve object y only if the clearance level of x is >= the classification level of y example: Alice’s clearance level is top secret, Bob’s is secret. Object O1’s classification level is top secret, O2’s is secret. Alice can retrieve both O1 and O2, Bob can only retrieve O2.
- #### user x can update object y only if the clearance level of x is equal to the classification level of y example: Alice can only update O1, Bob can only update O2.

### Encryption Algorithm Example

• use a secret encryption key
	

| data       | disciplina baza de date |
| ---------- | ----------------------- |
| secret key | student                 |


1. Create a table of codes
	• every character is associated with a number, for instance:
	![[Pasted image 20260530171806.png]]

2. Divide the message into blocks of length L, where L is the number of characters in the key 
	![[Pasted image 20260530171849.png]]

	replace every character in the message and every character in the key with their associated codes
	![[Pasted image 20260530171919.png]]

3. Add every number that corresponds to a character in a block with the number of the corresponding character in the key

	• if the obtained value is greater than n (in the example, n = 27), compute the remainder of the division by n
	![[Pasted image 20260530171953.png]]

4. replace the obtained numbers with their corresponding characters in the table of codes => a string that can be stored / transmitted
	-  the obtained string in the example: wbmgnceagvdgosxtyieruly

### Decryption

 - #### similar
 - #### in step 3, perform subtraction (modulo n) (instead of addition) 
 - #### one could also permute the original message and add values (to the characters' codes) for every position; or combine this method with the previous one



