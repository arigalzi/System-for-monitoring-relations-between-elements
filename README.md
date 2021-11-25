# System-for-monitoring-relations-between-elements

Implementation in standard C language (with only libc) of a program that reads a sequence of commands from standard input, each corresponding to a change in the entities or in the relationships between entities and, when required, produces on standard output, for each type of monitored relationship, the identifier of the entity that is the recipient of the largest number of instances of that relationship, and the number of relationships the entity receives.

Imagine, for example, a social network, where new users can register and existing users can delete their account, 
become "friends" with other users, break a friendship relationship, etc.
Relationships between entities are not necessarily symmetrical.
For example: Alice can be "friends" with Bruno, but the friendship is not reciprocated (Bruno is not Alice's friend).

## Commands

### Add

`addent ⟨ident⟩id_ent⟩` : Adds an entity identified by "id_ent" to the set of monitored entities; if the entity is already monitored, it does nothing.

### Delete

`delent ⟨ident⟩id_ent⟩` : Deletes the entity identified by "id_ent" from the set of monitored entities; eliminates all the relationships of which "id_ent" is a part
(both as origin and as destination).

### Add relationship

`addrel ⟨ident⟩id_orig⟩ ⟨ident⟩id_dest⟩ ⟨ident⟩id_rel⟩` : Adds a relationship - identified by "id_rel" - between the entities "id_orig" and "id_dest", where "id_dest" is the recipient of the relationship. If the relationship between "id_orig" and "id_dest" already exists, or if at least one of the entities is not monitored, it does nothing. The monitoring of the relationship type "id_rel" implicitly starts with the first "addrel" command concerning it.

### Delete relationship

`delrel ⟨ident⟩id_orig⟩ ⟨ident⟩id_dest⟩ ⟨ident⟩id_rel⟩` : Removes the relationship identified by "id_rel" between the entities "id_orig" and "id_dest" (where "id_dest" is the receiver of the relationship); if there is no "id_rel" relation between "id_orig" and "id_dest" (with "id_dest" as receiver), it does nothing.

### Output

`report` : Outputs the list of the relationships, reporting for each one the entities with the greatest number of incoming relationships, as
explained in continuation
removes the relationship identified by "id_rel" between the entities "id_orig" and "id_dest" (where "id_dest" is the receiver of the relationship);

### End 

`end` : End of input command sequence.


The mechanism monitors the following phenomena:
* A new entity begins to be monitored
* A monitored entity stops being monitored
* A new relationship is established between 2 monitored entities
* An existing relationship between 2 monitored entities ceases to exist
* Each entity has an identifying name (for example "Alice", "Bruno", "Carlo")
* There can be different types of relationships between entities, each identified by a name (e.g. "friend_of", "follows", "peer_of").
* Every relation has a line (for example, if Alice is "friend_of" Bruno, the line of the relation is
relationship is from Alice to Bruno, so Bruno is the "receiver" of the relationship), and is not
necessarily symmetrical
* Following a special command, the system returns, for each relationship, the entity that
has the maximum number of relations (if there are more entities whose number of received relations is maximum,
these are printed in increasing order of identification)
* The application will have to be optimized in order to manage a great number of entities and instances of
relations, but generally few types of relation

## Example of Input-Output

| INPUT  | OUTPUT   |
|---|---|
| addent "alice"  |   |
| addent "carlo"  |   |
| addent "bruno"  |   |
| addent "dario"  |   |
| report   | none  |
| addrel "carlo" "bruno" "amico_di"  |   |
| report  |  "amico_di" "bruno" 1;  |
| addrel "carlo" "alice" "amico_di"  |   |
| report  |  "amico_di" "alice" "bruno" 1;   |
| addrel "alice" "bruno" "amico_di"  |   |
| report  | "amico_di" "bruno" 2;  |
