# Cloning a repository

   ```bash
   git clone --recursive https://github.com/F7wu0Xhjsc5mVyRL/sm-takedamage-ext.git
   ```

> Recursive cloning required!

## Building via Docker

1. Build image
    ```bash
    docker build -t sm-takedamage-ext/build .
    ```
2. Run image (build extension)
    ```bash
    docker run -v .:/mnt/project --rm -it sm-takedamage-ext/build:latest
    ```