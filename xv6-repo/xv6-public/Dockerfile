# Use Ubuntu 18.04 which has binutils 2.30 (safe for xv6)
FROM ubuntu:18.04

# Install necessary packages including older binutils
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-multilib \
    gdb \
    qemu-system-x86 \
    git \
    make \
    binutils=2.30-21ubuntu1~18.04.9 \
    && rm -rf /var/lib/apt/lists/*

# Verify binutils version (should be 2.30.x which works with xv6)
RUN ld --version

# Create a working directory
WORKDIR /xv6

# Set up environment
ENV QEMU=qemu-system-i386

# Default command
CMD ["/bin/bash"]
