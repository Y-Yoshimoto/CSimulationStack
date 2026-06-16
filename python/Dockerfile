FROM python:slim-trixie
# https://hub.docker.com/_/python
LABEL maintaner='y-yoshimoto'

# Install apt package
RUN apt-get update \
    && apt-get install -y --no-install-recommends sudo inotify-tools git\
    && apt-get -y clean \
    && rm -rf /var/lib/apt/lists/* \
    && update-ca-certificates

### Python用短縮コマンド/ホットリロードシェルスクリプトを追加
### PYTHONPATH に共有ライブラリ用のパスを追加
COPY ./auxiliary/pythonWatch.sh /usr/local/bin/
RUN echo 'alias py="python"' >> /etc/bash.bashrc \
    && echo 'alias pyw="pythonWatch.sh"' >> /etc/bash.bashrc \
    && echo 'alias pyt="python -m unittest"' >> /etc/bash.bashrc \
    && echo 'export PYTHONPATH="/usr/src/shared:$PYTHONPATH"' >> /etc/bash.bashrc

### Install pip package
COPY requirements.txt ./
RUN pip install --upgrade pip \
    && pip install --no-cache-dir -r requirements.txt \
    && pip freeze > requirements.lock

# 実行ユーザー追加
ARG USERNAME=vscode
ARG USER_UID=501
ARG USER_GID=20
RUN useradd -m -s /bin/bash -u $USER_UID -g $USER_GID $USERNAME \
    && usermod -a -G 0 $USERNAME \
    && mkdir -p /vscode/vscode-server/ \
    && chown $USERNAME:dialout /vscode/vscode-server/.*

# Make workdir
WORKDIR /workspace/
RUN chown -R $USERNAME /workspace/
VOLUME /workspace/

ENTRYPOINT ["tail", "-f", "/dev/null"]