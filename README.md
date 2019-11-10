CONTRIBUTIONS - 
Chris Go: KD tree implementation.
Jack Arnolds: Trie implementation.
Finnegan Carroll: RPC calls.

STRUCTURES AND ALGORITHMS -
A Trie was used to match city/state names to their corresponding coordinates. 
A KD tree was used to locate the 5 closest airports given the client's coordinates.

THIRD PARTY CODE -

STRENGTHS AND WEAKNESSES - 
RPC: There was a ton of trouble getting the RPCs to work, it ended up being the case that clnt_create() in plane_server.c was setting errno to 13
which messed up the whole return list. As a result errno is set back to zero after the client is created. Additionally we decided to use a single 
struct with 6 char* to simplify our datatypes. This implementation is easier to debug and program but less extensible as we will only ever
beable to return 5 airports.

Trie:

KD tree:

RUNNING THE PROGRAM - 
make
./places&
./airports&
./client server1host server2host city state

