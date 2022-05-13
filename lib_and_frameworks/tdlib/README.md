# Tips
* On mac, 
    * needs assign openssl path, for example, `cmake ../ -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl@3 -DOPENSSL_LIBRARIES=/opt/homebrew/opt/openssl@3/lib`
    * or add 
    ```
    export OPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl@3/lib
    export LDFLAGS="-L/opt/homebrew/opt/openssl@3/lib"
    export CPPFLAGS="-I/opt/homebrew/opt/openssl@3/include"
    export PKG_CONFIG_PATH="/opt/homebrew/opt/openssl@3/lib/pkgconfig"
    ```
    in `~/.bashrc`.
