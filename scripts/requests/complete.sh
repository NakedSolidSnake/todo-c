#!/bin/bash

curl -X POST -s http://localhost:1234/complete \
  -H "Content-Type: application/json" \
  -d '{
    "id": "1"
  }' | jq .