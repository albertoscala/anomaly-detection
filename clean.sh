#!/bin/bash

# Remove .gch files in the current directory
find . -type f -name "*.gch" -delete

echo "All .gch files have been removed."