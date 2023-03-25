# Rena_HashCheckTool

Rena HashCheckTool是一套轻量化的文件哈希校验工具 支持单文件哈希计算 / 生成文件夹内文件哈希表 / 基于哈希表对文件进行批量校验

整套工具均使用C编写 依赖openssl和pthread库【若不开启多线程则不依赖pthread】

并留有外部调用api