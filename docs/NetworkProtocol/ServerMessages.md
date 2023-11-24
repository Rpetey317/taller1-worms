# Server packet structures

The general structure for a server packet is `<cd> <data...>`, where `cd` is a single byte identifying the type of message and `data` is all relevant packet info.

The possible values for such code and their semantic meaning are defined in `Common/NetworkProtocol.h` and further explained here. Unless specified otherwise, all types and constants referenced are defined in that file.

The structure of such data is defined by each packet type, and are explained in this file.

## Connection acknowledge

The first packet all clients receive upon successfully connecting to a server. It contains a single number representing the player's assigned ID. ID's are unique to each player and never change for the duration of a game, and the server always makes reference to players via their ID's.

The packet structure is

```
<cd> <id>
```

Where:

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the receiving player's assigned id.

## Player connected

Message sent when a new player connects, containing this new player's ID.

The packet structure is

```
<cd> <id>
```

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the new player's id.

## Player disconnected

Message sent when a player disconnects from the game, containing this new player's ID.

The packet structure is

```
<cd> <id>
```

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the disconnected player's id.

## Turn update

Message sent when a new turn begins, with the ID of the player whose turn is now.

The packet structure is

```
<cd> <id>
```

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the player whose turn is now.

## Chat message

A packet with a message sent to the lobby chat. It contains the owner's ID and the message content

The packet structure is

```
<cd> <id> <ln> <msg...>
```

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the author of the message.
- `<ln>` is a `strlen_t` representing the total length in bytes of the message.
- `<msg...>` is a (non-null termiated) string of `<ln>` bytes with the message.

## World Update

A packet containing all relevant world updates, meant to be sent every tick. It contains updated positions for all players [Will add more stuff in the near future]

The packet structure is:

```
<cd>
    <plcount>
        <id> <x> <y>
        <id> <x> <y>
        ...
```

- `<cd>` is the associated code
- `<plcount>` is a `amount_players_t` number with the amount of player positions to receive
- `<id>` is a player's id in `playerid_t`
- `<x> <y>` are the x and y coordinates in `point_t` of a player
