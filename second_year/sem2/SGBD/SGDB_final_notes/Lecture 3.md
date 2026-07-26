
## 1. Strict Two-Phase Locking (Strict 2PL)

- #### before a transaction can read / write an object, it must acquire a S / X lock on the object
* #### all the locks held by a transaction are released when it completes execution
- #### the Strict 2PL protocol allows only serializable schedules

---

## 2. Two-Phase Locking (2PL)

* #### before a transaction can read / write an object, it must acquire a S / X lock on the object
- #### once a transaction releases a lock, it cannot request other locks

--- 

## 3. Strict Schedules

- #### if transaction Ti has written object A, then transaction Tj can read and / or write A only after Ti ’s completion (commit / abort)

- #### strict schedules:
	- #### avoid cascading aborts
	- #### are recoverable schedules
	- #### if a transaction is aborted, its operations can be undone

- #### strict 2PL only allows strict schedules
--- 

## 4. Deadlocks

#### Core idea:
- #### T1 holds a lock on V1, T2 holds a lock on V2;
- #### T1 cannot obtain a lock on V2 because T2 holds it, but the same occurs on T2 -> it cannot obtain a lock on V1 because T1 has it. Both transactions wait for the other lock to be released.

![[Pasted image 20260529135152.png]]


## Prevention
- #### assign transactions timestamp-based priorities (each transaction has a timestamp - the moment it begins execution)
- #### the lower the timestamp, the older the transaction
- #### the older a transaction is, the higher its priority, with the oldest transaction having the highest priority
#### __2 deadlock prevention policies: Wait-die and Wound-wait__

- let's assume T1 wants to access an object locked by T2 (with a conflicting lock):
	- #### a) Wait-die:
		- #### if T1’s priority is higher, T1 can wait; otherwise, T1 is aborted
		- ![[Pasted image 20260529135729.png]]
		- #### T1 requests an X lock on object y, which is already locked with a conflicting lock by T2
		- #### since T1 has a higher priority, it is allowed to wait
		- #### T2 asks for an X lock on object x, already locked with a conflicting lock by T1
		- #### since T2 has a lower priority, it is aborted
		- #### T1 now obtains the requested lock on object y and proceeds with the write operation
		
	- #### b) Wound-wait
		- #### if T1’s priority is higher, T2 is aborted; otherwise, T1 can wait
		- ![[Pasted image 20260529140540.png]]
		- #### T1 requests an X lock on object y, which is already locked with a conflicting lock by T2
		- #### since T1 has a higher priority, T2 is aborted
		- #### T1 obtains the requested lock on object y and continues execution

waits-for graph
• structure maintained by the lock manager to detect deadlock cycles

---

## 5. Isolation Levels

- #### determines the degree to which a transaction is exposed to the operations of other concurrently running transactions

1) READ UNCOMMITED
	- #### a transaction T can read data modified by an ongoing transaction (uncommitted data)
	- #### lowest degree of isolation
	- #### no S locks when reading data
	- #### dirty reads, unrepeatable reads, phantoms can happen
	- #### exclusive locks need to be acquired for writing (writes always need X locks)
	
2) READ COMMITTED
	- #### a transaction T can only read committed data
	- #### however, an object read by T can be changed by another transaction while T is in progress
	- #### a transaction must acquire an exclusive lock prior to writing an object
	- #### a transaction must acquire a shared lock prior to reading an object (i.e., the last transaction that modified the object is finished)
	- #### exclusive locks are released at the end of the transaction
	- #### shared locks are immediately released
	- #### unrepeatable reads, phantoms can happen

3) REPEATABLE READ
	- #### a transaction T can only read committed data
	- #### no object read by T can be changed by another transaction while T is in progress (if T reads an object O twice, no transaction can modify O between T's reads)
	- #### a transaction must acquire an exclusive lock prior to writing an object
	- #### a transaction must acquire a shared lock prior to reading an object
	- #### exclusive locks are released at the end of the transaction
	- #### shared locks are released at the end of the transaction
	- #### phantoms can happen
	
4) SERIALIZABLE
	- #### a transaction T can only read committed data
	- #### no object read by T can be changed by another transaction while T is in progress
	- #### if T reads a set of objects based on a search predicate, this set cannot be changed by other transactions while T is in progress
	- #### a transaction must acquire locks on objects before reading / writing them
	- #### a transaction also acquires locks on sets of objects that must remain unmodified
	- #### if query SELECT * FROM Students WHERE GPA >= 8 is executed twice within a transaction, it must return the same answer set
	- #### locks are held until the end of the transaction
	- #### highest degree of isolation, transaction basically don't run in parallel anymore 











