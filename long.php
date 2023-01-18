<?php

// Emulates a long running script.
// This is used for testing if the Apache module actually skips
// content creation phase while processing request.

sleep(2);

print("Hi from a long running script.\n");
