# Server packet structures

The general structure for a server packet is `<cd> <data...>`, where `cd` is a single byte identifying the type of message and `data` is all relevant packet info. The sole exception is the game start signal, which is just a single byte.

The possible values for such code and their semantic meaning are defined in `Common/NetworkProtocol.h` and further explained here. Unless specified otherwise, all types and constants referenced are defined in that file.

The structure of such data is defined by each packet type, and are explained in this file.

## Game Start

The first message all clients receive upon successfully connecting to a server. It signals that the game has started sending a single byte. So the (pretty simple structure) of the message is:

```
<cd>
```

Where:

- `<cd>` is the associated code

## Connection acknowledge

The second packet all clients receive upon successfully connecting to a server and starting a game. It contains a single number representing the player's assigned ID. ID's are unique to each player and never change for the duration of a game, and the server always makes reference to players via their ID's.

The packet structure is

```
<cd> <pid>
```

Where:

- `<cd>` is the associated code
- `<pid>` is a `playerid_t` number representing the receiving player's assigned id.

## Player connected

Message sent when a new player connects, containing this new player's ID.

The packet structure is

```
<cd> <pid>
```

- `<cd>` is the associated code
- `<pid>` is a `playerid_t` number representing the new player's id.

## Player disconnected

Message sent when a player disconnects from the game, containing this new player's ID.

The packet structure is

```
<cd> <pid>
```

- `<cd>` is the associated code
- `<pid>` is a `playerid_t` number representing the disconnected player's id.

## Turn update

Message sent when a new turn begins, with the ID of the player whose turn is now.

The packet structure is

```
<cd> <id>
```

- `<cd>` is the associated code
- `<id>` is a `playerid_t` number representing the worm whose turn is now.

## Chat message

A packet with a message sent to the lobby chat. It contains the owner's ID and the message content

The packet structure is

```
<cd> <pid> <ln> <msg...>
```

- `<cd>` is the associated code
- `<pid>` is a `playerid_t` number representing the author of the message.
- `<ln>` is a `strlen_t` representing the total length in bytes of the message.
- `<msg...>` is a (non-null termiated) string of `<ln>` bytes with the message.

## World Update

A packet containing all relevant world updates, meant to be sent at least once every tick. It contains updated positions for all players

The packet structure is:

```
<cd>
    <plcount>
        <id> <x> <y> <state> <pid> <hp> <ln> <map...>
        <id> <x> <y> <state> <pid> <hp> <ln> <map...>
        ...
    <wpcount>
        <id> <x> <y> <angle> <wid>
        <id> <x> <y> <angle> <wid>
        ...
```

- `<cd>` is the associated code
- `<plcount>` is a `amount_players_t` number with the amount of player positions to receive
- `<id>` is a worms's id in `playerid_t`
- `<x> <y>` are the x and y coordinates in `point_t` of a player/weapon
- `<pid>` is the respective player's id in `playerid_t`
- `<hp>` are the worm's current hitpoints left
- `<ln>` is the length of...
- `<map>`, which a string representing the map's name
- `<wpcount>` is the number of weapons (projectiles) to receive
- `<angle>` is the weapon's current facing angle
- `<wid>` is the respective weapon id

## Timer update

An update sent at least once every server tick to inform players of time left on current turn.

The packet structure is:

```
<cd> <t> <id>
```

- `<cd>` is the associated code
- `<t>` is the time left (in seconds).
- `<id>` is a `playerid_t` number representing the worm whose turn is currently.
