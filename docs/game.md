## Game
(c) Alan Ludwig, All rights reserved 

A game of rock-paper-scissors


```mermaid
sequenceDiagram
    actor Alice
    Actor Bob
    Alice->>Bob: "Play?"
    Bob->>Alice: "Yes!"
    Alice->>Bob: "Rock" or "Paper" or "Scissors"
    Bob->>Alice: "Rock" or "Paper" or "Scissors"
    Alice->>Bob : "You Win" or "I Win" or "Tie"
    Bob->>Alice : "You Win" or "I Win" or "Tie"
```




``` mermaid
stateDiagram-v2

# Start
[*] --> IDLE

# IDLE
    IDLE --> MOVE : MOVE_PLAY (Send Yes + ROCK/PAPER/SCISSORS)
    IDLE --> INVITE : MOVE_START (Send Play)

# invite
    INVITE --> MOVE: MOVE_YES (Send ROCK/PAPER/SCISSORS)

# MOVE
   MOVE --> RESULT : MOVE_ROCK/PAPER/SCISSORS (Send YOU_WIN/I_WIN/TIE)

# RESULT
    RESULT --> IDLE : MOVE_YOU_WIN/I_WIN/TIE



```
## Total Vocabulary
    PLAY: PL
    YES: YE
    ROCK: R
    PAPER : PA
    SCISSORS: SC
    YOU WIN: YO
    I WIN: I
    TIE: T



Command Parser
```mermaid
stateDiagram-v2

[*] --> Idle


#Idle
Idle --> P : P
Idle --> Y : Y
Idle --> ROCK : R
Idle --> Scissors : S
Idle --> TIE : T
Idle --> I_WIN : I
Idle --> Idle : whitespace
Idle --> SKIP : anything else

#P
P --> PLAY : L
P --> PAPER : A
P --> SKIP : else


# PLAY
PLAY --> SKIP : fire on_play

#Y
Y --> YES : E
Y --> YOU_WIN : O
Y --> SKIP : else


#YES
YES --> SKIP 

#ROCK
ROCK --> SKIP 

#PAPER
PAPER --> SKIP : fire on_paper


#SCISSORS
Scissors --> SKIP : fire on_scissors

#YOU WIN
YOU_WIN --> SKIP : fire on_you_win


#I WIN
I_WIN --> SKIP : fire on_i_win

#TIE
TIE --> SKIP : fire on_tie

# SKIP
SKIP --> [*] : cr
SKIP --> SKIP : ~cr




```