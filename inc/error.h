#pragma once

// (C) Alan Ludwig, All rights reserved

// Errors

constexpr int ERROR_SUCCESS = 0;                     // SUCCESS!
constexpr int ERROR_CHARACTER_QUEUE_FULL = 1;        // the parser character queue is full, input has been dropped
constexpr int ERROR_UNEXPECTED_CMD_PARSER_STATE = 3; // command parser is in an unexpected state.
constexpr int MOVE_QUEUE_FULL = 3; // command parser is in an unexpected state.
