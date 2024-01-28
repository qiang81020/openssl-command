
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [记录学习过程中未明白的内容](#记录学习过程中未明白的内容)
  - [openssl command](#openssl-command)
    - [1. 盐值的作用机制](#1-盐值的作用机制)
    - [2. pkeyutl](#2-pkeyutl)
  - [知识点](#知识点)
    - [0. ECC算法原理](#0-ecc算法原理)
    - [1. RSA加密填充模式](#1-rsa加密填充模式)
    - [2. DSA算法](#2-dsa算法)
    - [3. CMAC](#3-cmac)
    - [4. HMAC](#4-hmac)
    - [5. GMAC](#5-gmac)

<!-- /code_chunk_output -->


# 记录学习过程中未明白的内容

## openssl command

### 1. 盐值的作用机制

- 对称算法

- 非对称算法

### 2. pkeyutl

- 协商会话密钥 -derive, -peerkey组合使用

- KDF 密钥派生函数

## 知识点

### 0. ECC算法原理

[ECC算法原理](https://zhuanlan.zhihu.com/p/42629724)

### 1. RSA加密填充模式

- none

- oaep

- pkcs1

- x931

### 2. DSA算法

### 3. CMAC

[CMAC wiki](https://en.wikipedia.org/wiki/One-key_MAC)

### 4. HMAC

$$
HMAC(K, m) = H((K' \oplus opad) || H((K' \oplus ipad) || m))  \\
K'= \begin{cases}
H(K) &if\ K\ is\ larger\ than\ block\ size\\
K    &otherwise
\end{cases} \\
\\
ipad=0x5c..0x5c
opad=
$$

| Hash function H | b bytes  | L, bytes |
|-----------------|----------|----------|
| MD5             | 64       | 16       |
| SHA-1           | 64       | 20       |
| SHA-224         | 64       | 28       |
| SHA-256         | 64       | 32       |
| SHA-512/224     | 128      | 28       |
| SHA-512/256     | 128      | 32       |
| SHA-384         | 128      | 48       |
| SHA-512         | 128      | 64       |
| SHA3-224        | 144      | 28       |
| SHA3-256        | 136      | 32       |
| SHA3-384        | 104      | 48       |
| SHA3-512        | 72       | 64       |

### 5. GMAC