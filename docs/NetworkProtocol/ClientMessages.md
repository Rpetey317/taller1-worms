# Client packet structures

The general Client packet format is the code of the specific action message and another value if neededs, like this:
 <cd> <data ...> , where <cd> is the message code of the action. The structure of <data...> depends of each specific
 action and is explained in his file.


The client can send the following actions:


# Jump
When SDL pushes a jump action, the sender threads sends the action through the protocol. The format of this action is:
 ```
 <cd>
 ```
 Where:

- `<cd>` can be the message code of forward jump (0x10) or the message code of backards jump (0x11)


 # Message
The format of this action is:
 ```
 <cd> <msglen> <msg>, 
 ```
 Where:
  `<cd>` is the message code (0x09), 
  `<msglen>` is the lenght of the message
  `<msg>` is the string msg

# Move 
The format of this action is:
 ```
 <cd>
 ```
 Where:

- `<cd>` can be the message code of move right (0x07) or the message code of move left (0x08)


# Null
The format of this action is:
 ```
 <cd>
 ```
 Where:

- `<cd>` is the message code of the null action (0x13)
