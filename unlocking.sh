#!/bin/bash

# Define the name of the zip file
zip_file_name="/home/compleks/tester/locked_folder.zip"

# Define the password for the zip file (if any)
zip_password="mysecret"

# Extract the contents of the zip file to a new directory
unzip -P "$zip_password" "$zip_file_name" > /dev/null

# Delete the zip file
rm "$zip_file_name"

#giving read write permissions back to the file
chmod a+w lockedfile.txt


echo "Zip file extracted: $zip_file_name"
