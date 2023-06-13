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

# receive an invite
    [*] --> Idle

    note left of Idle
        All errors 
        (including 2 second timeout) 
        return to idle state
    end note

    Idle --> Invited : receive invite
    Invited --> Move : send yes
    Move --> over : send move
    over --> Idle : game over received

# send an invite
    Idle --> Invite : send invite
    Invite --> Move : receive yes


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
# PLAY
Idle --> P : P

P --> PLAY : L


#YES
Idle --> Y : Y
Y --> YES : E

#ROCK
Idle --> ROCK : R

#PAPER
P --> PAPER : A

#SCISSORS
Idle --> Scissors : S

#YOU WIN
Y --> YOU_WIN : 0

#I WIN
Idle --> I_WIN : I

#TIE
Idle --> TIE : T

# SKIP
Idle --> SKIP : anything else

SKIP --> [*] : cr




```