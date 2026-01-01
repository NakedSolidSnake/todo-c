#!/bin/bash

TYPE=$1
echo $TYPE

curl -X GET -s "http://localhost:1234/schema?filter=${TYPE}" | jq .