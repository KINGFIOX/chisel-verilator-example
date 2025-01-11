FROM mcr.microsoft.com/devcontainers/base:jammy

# install scala environment && win far ahead
RUN apt-get update && apt-get install -y openjdk-17-jdk
COPY install.sh /tmp/install.sh
ENV https_proxy=http://10.249.12.73:20171 http_proxy=http://10.249.12.73:20171 all_proxy=socks5://10.249.12.73:20170
RUN chmod +x /tmp/install.sh \
    && export _REMOTE_USER=vscode \
    && /tmp/install.sh
ENV https_proxy="" http_proxy="" all_proxy=""

# install clangd cmake
RUN apt-get update && apt-get install -y clangd cmake

# install verilator

