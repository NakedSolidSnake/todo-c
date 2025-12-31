#!/bin/bash

curl -X PUT -s http://localhost:1234/update \
  -H "Content-Type: application/json" \
  -d '{
    "id": "1",
    "name": "Update para produção",
    "description": "Fazer update da aplicação"
  }' | jq .