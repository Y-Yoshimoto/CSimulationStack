FROM python:slim-trixie
LABEL maintainer='y-yoshimoto'

## uvインストール
RUN --mount=type=cache,mode=0755,target=/root/.cache/pip \
    pip install uv && uv cache clear

# aptインストール / C++開発環境構築
ARG APT_CACHE_ID=apt-cache-C
RUN --mount=type=cache,id=${APT_CACHE_ID},target=/var/cache/apt,sharing=locked \
    --mount=type=cache,id=${APT_CACHE_ID},target=/var/lib/apt,sharing=locked \
    apt-get update \
    && apt-get install -y --no-install-recommends \
    git make jq curl wget sudo\
    clang clangd clang-format clang-tidy \
    gdb \
    googletest \
    libgtest-dev libboost-all-dev \
    build-essential cmake\
    pipx \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# メルセンヌツイスタ(https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/index-jp.html)のインストール
# リンクコンパイルコマンドサンプル(gcc -O3 main.c -lsfmt -o main )
RUN curl -L https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/SFMT-src-1.5.1.tar.gz -O \
    && tar -xzf SFMT-src-1.5.1.tar.gz \
    && cd SFMT-src-1.5.1 \
    && mkdir -p /usr/local/include/SFMT \
    && cp SFMT.*h /usr/local/include/SFMT/ \
    # --msse2オプションはSSE2命令を使用する/ARM環境では利用できないため、clangでコンパイルするようにする
    && gcc -O3 -std=c99 -msse2 -DHAVE_SSE2 -c SFMT.c -o SFMT.o || clang -O3 -std=c99 -c SFMT.c -o SFMT.o \
    && ar rcs libSFMT.a SFMT.o \
    && mv libSFMT.a /usr/local/lib/ \
    && rm -rf SFMT-src-1.5.1*
    

# 実行ユーザー/作業ディレクトリ作成
ARG USERNAME=vscode
ARG UID=1000
ARG GID=20
RUN useradd --non-unique -m -s /bin/bash -u $UID -g $GID $USERNAME \
    && usermod -a -G 0 $USERNAME \
    && mkdir -p /usr/dev \
    && chown -R $USERNAME /usr/dev \
    && mkdir -p /vscode/vscode-server/ \
    && chown $USERNAME /vscode/vscode-server/.*

# initファイルのコピー
COPY ./auxiliary/docker-entrypoint.sh /usr/bin/docker-entrypoint.sh
RUN chmod +x /usr/bin/docker-entrypoint.sh
### Python用短縮コマンド/ホットリロードシェルスクリプトを追加
COPY ./auxiliary/pythonWatch.sh /usr/local/bin/
RUN echo 'alias py="python"' >> /etc/bash.bashrc \
    && echo 'alias pyw="pythonWatch.sh"' >> /etc/bash.bashrc \
    && echo 'export pyt="python -m pytest"' >> /etc/bash.bashrc \
    && echo 'export pytest="python -m pytest"' >> /etc/bash.bashrc

WORKDIR /usr/dev
VOLUME /usr/dev

ENTRYPOINT ["/usr/bin/docker-entrypoint.sh"]
## デバック用
CMD [ "tail", "-f", "/dev/null"]