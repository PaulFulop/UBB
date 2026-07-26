## 1. Normal execution

• during normal execution, transactions read / write database objects
• reading database object O:
	• bring O from disk into a frame in the Buffer Pool (BP)
	• copy O’s value into a program variable
	
• writing database object O:
	• modify an in-memory copy of O (in the BP)
	• write the in-memory copy to disk
	![[Pasted image 20260529153442.png]]


## DISK ←→ BUFFER POOL (in RAM) ←→ TRANSACTION (execution)

1) DISK:
	- this is where the db is stored
	- organized into pages -> fixed size chunks (4kb/8kb)
	- cheap and large but slow to access
2) BUFFER POOL:
	- region of main memory managed by the DBMS
	- divided into frames -> each frame can hold exactly one page
	- fast to access but limited in size
	- like a cache for disk pages
---
## 2. Writing Objects

- ### Options:
	- transaction T changes object O (in frame F in the BP):
		- #### steal approach:
			- #### T’s changes can be written to disk before it commits
			- #### transaction T2 needs a page
			- #### the BM chooses F as a replacement frame (while T is in progress)
			- #### T2 steals a frame from T
			
		- #### no-steal approach:
			- #### T’s changes cannot be written to disk before it commits
			
		- #### force approach:
			- #### T’s changes are immediately forced to disk when it commits

		- #### no-force approach:
			- #### T’s changes are not forced to disk when it commits

• no-steal approach
	• advantage - changes of aborted transactions don’t have to be undone (such changes are never written to disk!)
	• drawback - assumption: all pages modified by active transactions can fit in the BP
	
• force approach
	• advantage - actions of committed transactions don’t have to be redone
	• by contrast, when using no-force, the following scenario is possible: transaction T commits at time t0 ; its changes are not immediately forced to disk; the system crashes at time t1 => T’s changes have to be redone!
---

## 3.ARIES

- recovery algorithm; steal, no-force approach
- system restart after a crash - three phases:
	- #### analysis - determine:
		- #### active transactions at the time of the crash
		- #### dirty pages, i.e., pages in BP whose changes have not been written to disk
	 - #### redo: reapply all changes (starting from a certain record in the log), i.e., bring the DB to the state it was in when the crash occurred
	 - #### undo: undo changes of uncommitted transactions

Checkpointing: reduce the amount of work performed by the system when it comes back up after a crash

