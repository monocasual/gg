FROM alpine:edge
LABEL maintainer="monocasual@gmail.com"

# Install dependencies.

RUN apk add --no-cache sdl2-dev sdl2_ttf-dev build-base

# Create user.

RUN adduser -S normaluser && echo "normaluser:normaluser" | chpasswd
USER normaluser

# Change working dir. 

#WORKDIR /home/gg
