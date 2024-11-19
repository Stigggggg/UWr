## Zad. 1

**Atomicity** - each statement in transaction (read, write, update or delete) is treated as a single unit. Either the entire statement is executed, or none. It prevents data loss and corruption from occurring if, for example, your streaming data source fails during the stream.

**Consistency** - ensures that transactions only make changes to tables in predefined, predictable ways. In terms of transactions consistency ensures that corruption or erros in data do not create unintended consequences for the integrity of tables. 

**Isolation** - when multiple users are reading and writing from the same table all at once, it ensures that the concurrent transactions do not interfere or affect each other. Each request can occur as though they were occuring one by one.

**Durability** - ensures that changes to your data made by succesfully executed transactions will be saved, even if a system failure appears.

ACID transactions ensure the highest possible data reliability and integrity. They ensure that your data never falls into an inconsistent state because of an operation that only partially completes. For example, without ACID transactions, if you were writing some data to a database table, but the power went out unexpectedly, it's possible that only some of your data would have been saved, while some of it would not. Now your database is in an inconsistent state that is very difficult and time-consuming to recover from.