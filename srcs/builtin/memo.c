//builtin関数
//echo: (-n オプションの挙動を含む)
//cd: (相対パス、または絶対パスのみで動作する)
//pwd: (オプションの処理を含まない)
//export: (オプションの処理を含まない)
//unset: (オプションの処理を含まない)
//env: (オプションと引数の処理を含まない)
//exit: (オプションの処理を含まない)

//dup(), dup2(), dup3()は、ファイルディスクリプタを複製する。
//int dup(int oldfd);
//int dup2(int oldfd, int newfd);
//int dup3(int oldfd, int newfd, int flags);