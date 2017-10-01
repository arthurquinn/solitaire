#pragma once

#define NUM_CARDS                   52
#define NUM_CARDS_IN_SUIT           13

#define HEARTS                      0
#define DIAMONDS                    1
#define SPADES                      2
#define CLUBS                       3

#define RED                         0
#define BLACK                       1

#define NUM_FOUNDATION_PILES        4
#define NUM_TABLEAU_PILES           7

#define STOCK                       0
#define TALON                       1
#define FOUNDATION                  2
#define FOUNDATION_LAST             5
#define TABLEAU                     6
#define TABLEAU_LAST                12

#define RESPONSE_KEY                "response"
#define REASON_KEY                  "reason"
#define UPDATE_KEY                  "update"
#define PUSH_KEY                    "push"
#define POP_KEY                     "pop"
#define PILE_KEY                    "pile"

#define ENGINE_RESPONSE_OK          "ok"
#define ENGINE_RESPONSE_READY       "ready"
#define ENGINE_RESPONSE_ERROR       "error"

#define COMMAND_PARSE_ERROR         "PARSE_ERROR"

#define MOVE                        "move"
#define DRAW                        "draw"

#define NO_REASON                   "..."
#define EMPTY_RESPONSE               ""
#define ERROR_TAG                   "[Error]"
#define INVISIBLE_CARD              "xx"
