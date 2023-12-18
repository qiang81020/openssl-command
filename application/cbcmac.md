
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [CBC-MAC](#cbc-mac)
  - [支持的CBC模式的算法](#支持的cbc模式的算法)
  - [EXAMPLE](#example)
    - [AES 128,192,256, SM4](#aes-128192256-sm4)
    - [ANSI X9.9 MAC (single DES)](#ansi-x99-mac-single-des)
    - [ANSI X9.19 MAC (double DES)](#ansi-x919-mac-double-des)

<!-- /code_chunk_output -->


# CBC-MAC

由于在openssl中没有对CBC-MAC直接的计算，所以需要通过alg-cbc标识对数据进行加密并计算最后一个分组长度的密文并输出，作为mac的值。

***NOTICE:*** 
1. 由于是使用加密替代，所有只能使用加密算法默认的的填充方式——pkcs1v1-5。此填充方式与标准mac计算的填充方式完全不同。应手动填充为分组长度并使用-nopad标志进行计算

2. 128: iv 16B, group len 16B, keylen 16B
3. 192: iv 16B, group len 16B, keylen 24B
4. 256: iv 16B, group len 16B, keylen 32B

## 支持的CBC模式的算法

- 查看支持的cbc算法

```bash
# tr 分割字符串，分别使用空格" "和回车”\012"分割
openssl enc -list | tr -s " " "\012" | grep cbc

root@84682ea0c33e:/hostfile/mac# openssl enc -list | tr -s " " "\012" | grep cbc
-aes-128-cbc
-aes-192-cbc
-aes-256-cbc
-aria-128-cbc
-aria-192-cbc
-aria-256-cbc
-bf-cbc
-camellia-128-cbc
-camellia-192-cbc
-camellia-256-cbc
-cast-cbc
-cast5-cbc
-des-cbc
-des-ede-cbc
-des-ede3-cbc
-desx-cbc
-idea-cbc
-rc2-40-cbc
-rc2-64-cbc
-rc2-cbc
-seed-cbc
-sm4-cbc
```

## EXAMPLE

- 数据准备
  - mac数据

```bash
# 使用系统随机数生成原始文件
head -c 192 /dev/random > plain.bin
```

  - iv

    - 8 : 0000000000000000
    - 16: 00000000000000000000000000000000

  - key
    -  8B (64bits): 0001020304050607
    - 16B (128bits): 000102030405060708090A0B0C0D0E0F
    - 24B (192bits): 000102030405060708090A0B0C0D0E0F1122334455667788
    - 32B (256bits): 000102030405060708090A0B0C0D0E0F11223344556677889900AABBCCDDEEFF

### AES 128,192,256, SM4

- aes-128-cbc

```bash
echo 11223344556677889900AABBCCDDEEFF | xxd -r -p | \
openssl enc -aes-128-cbc -iv 00000000000000000000000000000000 \
-K 000102030405060708090A0B0C0D0E0F -nopad | tail -c 16 | xxd

root@84682ea0c33e:/hostfile/mac# echo 11223344556677889900AABBCCDDEEFF | xxd -r -p | \
openssl enc -aes-128-cbc -iv 00000000000000000000000000000000 \
-K 000102030405060708090A0B0C0D0E0F -nopad | tail -c 16 | xxd
00000000: 6cf0 74d9 1884 8c64 2691 f802 6c22 d6fc  l.t....d&...l"..
```

- aes-192-cbc

```bash
# len(iv) = 16, len(key) = 24, len(data block) = 24
openssl enc -aes-192-cbc -iv 00000000000000000000000000000000 \
-K 000102030405060708090A0B0C0D0E0F1122334455667788 -in plain.bin \
-nopad | tail -c 16 | xxd
```


- aes-256-cbc

```bash
# len(iv) = 16, len(key) = 24, len(data block) = 24
openssl enc -aes-256-cbc -iv 00000000000000000000000000000000 \
-K 000102030405060708090A0B0C0D0E0F11223344556677889900AABBCCDDEEFF -in plain.bin \
-nopad | tail -c 16 | xxd
```

- sm4-cbc

```bash
# len(iv) = 16, len(key) = 24, len(data block) = 24
openssl enc -sm4-cbc -iv 00000000000000000000000000000000 \
-K 000102030405060708090A0B0C0D0E0F -in plain.bin \
-nopad | tail -c 16 | xxd
```

### ANSI X9.9 MAC (single DES)

```bash
# 当需要使用des算法，需要增加 -provider legacy
# key = 0102030405060708
# iv  = 0000000000000000
# data (len % 8 == 0, padding 0x00)
#     = 6cf074d918848c642691f8026c22d6fc71067f32f9538a42ebe9709d51350000
echo 6cf074d918848c642691f8026c22d6fc71067f32f9538a42ebe9709d51350000 \
| xxd -r -p \
| openssl enc -des-cbc -iv 0000000000000000 -K 0102030405060708 -nopad \
-provider legacy | tail -c 8 | xxd

root@84682ea0c33e:/hostfile/mac# echo 6cf074d918848c642691f8026c22d6fc71067f32f9538a42ebe9709d51350000 | xxd -r -p | openssl enc -des-cbc -iv 0000000000000000 -K 0102030405060708 -nopad -provider legacy | tail -c 8 | xxd
00000000: 8f1c 0fc6 a8e3 7cec                      ......|.
```

### ANSI X9.19 MAC (double DES)

```bash
# 当需要使用des算法，需要增加 -provider legacy
# key = 0102030405060708 1122334455667788
# iv  = 0000000000000000
# data (len % 8 == 0, padding 0x00)
#     = 6cf074d918848c642691f8026c22d6fc71067f32f9538a42ebe9709d51358000
# 使用key前8字节对数据前len - 8字节做des-cbc, 后使用完整的key对最后8字节做des-ede-cbc
# 填充模式为80000...(8B),整8字节不填充

# step 1
echo 6cf074d918848c642691f8026c22d6fc71067f32f9538a42\
| xxd -r -p \
| openssl enc -des-cbc -iv 0000000000000000 \
-K 0102030405060708 -nopad \
-provider legacy | tail -c 8 | xxd -p
# step 2
echo ebe9709d51358000 \
| xxd -r -p \
| openssl enc -des-ede-cbc -iv 3f6d6527f9b52ee9 \
-K 01020304050607081122334455667788 -nopad \
-provider legacy | tail -c 8 | xxd -p
```
