# Use an official base image with a C++ environment
FROM ubuntu:latest

# Install build dependencies (update the package lists, install g++, make)
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    pkg-config \
    libglib2.0-dev \
    python3 \
    python3-pip

RUN pip install requests


# Set the working directory in the container
WORKDIR /app

# Copy the source code into the container
COPY src/ /app/

# Compile the application using the Makefile
RUN make

EXPOSE 5000

# The command to run when the container starts
CMD ["python3", "wrapper.py"]
