#!/bin/bash

curl -X POST -s http://localhost:1234/create \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Deploy para produção",
    "description": "Fazer deploy da aplicação"
  }' | jq .