#!/bin/bash

curl -X POST -s http://localhost:1234/shutdown \
  -H "Content-Type: application/json" \
  -d '{
    "command": "yes"
  }' | jq .