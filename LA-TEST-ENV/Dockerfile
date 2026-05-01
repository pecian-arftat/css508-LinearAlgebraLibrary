FROM ubuntu:22.04

# Avoid prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Build
RUN cmake -S . -B build
RUN cmake --build build

# Run tests
CMD ["ctest", "--test-dir", "build", "--output-on-failure"]