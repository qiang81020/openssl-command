
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

# Cryptographic Message Syntax (CMS) ( 未完 )

[标准](https://www.rfc-editor.org/rfc/rfc5652#page-7)

pkcs7加密语法格式

## 前言

- 摘要

本文档描述了加密消息语法 (CMS)。 此语法用于对任意消息内容进行数字签名、摘要、身份验证或加密。

- 本备忘录的状态

本文件规定了互联网社区的互联网标准跟踪协议，并请求讨论和提出改进建议。 请参阅当前版本的《互联网官方协议标准》（STD 1）了解该协议的标准化状态和状态。 本备忘录的分发不受限制。

- 版权和许可声明

版权所有 (c) 2009 IETF Trust 和文档作者。 版权所有。

本文档受本文档发布之日生效的 BCP 78 和 IETF Trust 与 IETF 文件相关的法律规定 (<http://trustee.ietf.org/license-info>) 的约束。 请仔细阅读这些文件，因为它们描述了您与本文件相关的权利和限制。 从本文档中提取的代码组件必须包括信托法律条款第 4.e 节中所述的简化 BSD 许可证文本，并且如 BSD 许可证中所述，不提供任何保证。

本文档可能包含 2008 年 11 月 10 日之前发布或公开发布的 IETF 文档或 IETF 贡献中的材料。控制本材料某些内容版权的人员可能未授予 IETF 信托允许修改此类材料的权利 在 IETF 标准流程之外。 未经控制此类材料版权的人的充分许可，不得在 IETF 标准流程之外修改本文档，并且不得在 IETF 标准流程之外创建其衍生作品，除非对其进行格式化 以 RFC 形式发布或将其翻译成英语以外的语言。

## 1. 介绍

本文档描述了加密消息语法 (Cryptographic Message Syntax. CMS)。 此语法用于对任意消息内容进行数字签名、摘要、身份验证或加密。

CMS描述了用于数据保护的封装语法。 它支持数字签名和加密。 语法允许多重封装； 一个封装信封可以嵌套在另一个封装信封内。 同样，一方可以对一些先前封装的数据进行数字签名。 它还允许将任意属性（例如签名时间）与消息内容一起签名，并提供与签名关联的其他属性（例如联署）。

CMS 可以支持多种基于证书的密钥管理架构，例如 PKIX（使用 X.509 的公共密钥基础设施）工作组 [PROFILE] 定义的架构。

CMS 值是使用 ASN.1 [X.208-88] 和 BER 编码（基本编码规则）[X.209-88] 生成的。 值通常表示为八位字节字符串。 虽然许多系统能够可靠地传输任意八位字节串，但众所周知，许多电子邮件系统却不能。 本文档不涉及对八位字节字符串进行编码以在此类环境中进行可靠传输的机制。

### 1.1 CMS 的演变

CMS 源自 PKCS #7 版本 1.5，该版本记录在 RFC 2315 [PKCS#7] 中。 PKCS #7 版本 1.5 是在 IETF 之外开发的； 它最初于 1993 年 11 月作为 RSA 实验室技术说明发布。从那时起，IETF 就开始负责 CMS 的开发和维护。 如今，几个重要的 IETF 标准跟踪协议都使用 CMS。

本节介绍 IETF 在每个已发布版本中对 CMS 所做的更改。

#### 1.1.1. 自 PKCS #7 版本 1.5 以来的变化

RFC 2630 [CMS1] 是 IETF 标准轨道上 CMS 的第一个版本。 只要有可能，就会保留与 PKCS #7 版本 1.5 的向后兼容性； 但是，进行了更改以适应版本 1 属性证书传输并支持独立于算法的密钥管理。 PKCS #7 版本 1.5 仅支持密钥传输。 RFC 2630 增加了对密钥协商和先前分布式对称密钥加密密钥技术的支持。

#### 1.1.2. 自 RFC 2630 以来的变化

RFC 3369 [CMS2] 废弃了 RFC 2630 [CMS1] 和 RFC 3211 [PWRI]。 基于密码的密钥管理包含在 CMS 规范中，并且指定了一种扩展机制来支持新的密钥管理方案，而无需对 CMS 进行进一步更改。 保留与 RFC 2630 和 RFC 3211 的向后兼容性； 但是，添加了版本 2 属性证书传输，并且不推荐使用版本 1 属性证书。

安全/多用途 Internet 邮件扩展 (S/MIME) v2 签名 [MSG2] 基于 PKCS #7 版本 1.5，与 S/MIME v3 签名 [MSG3] 和 S/MIME v3.1 签名 [MSG3.1] 兼容 ]。 但是，基于 PKCS #7 版本 1.5 的签名存在一些微妙的兼容性问题。 这些问题将在第 5.2.1 节中讨论。 当前版本的 CMS 仍然存在这些问题。

本文档中未讨论特定的加密算法，但在 RFC 2630 中对其进行了讨论。特定加密算法的讨论已移至单独的文档 [CMSALG]。 协议和算法规范的分离使得IETF可以独立更新每个文档。 该规范不要求实现任何特定算法。 相反，依赖 CMS 的协议应为其环境选择适当的算法。 算法可以选自[CMSALG]或其他地方。

#### 1.1.3. 自 RFC 3369 以来的变化

RFC 3852 [CMS3] 已废弃 RFC 3369 [CMS2]。 正如上一节所讨论的，RFC 3369 引入了一种扩展机制来支持新的密钥管理方案，而无需对 CMS 进行进一步更改。 RFC 3852 引入了类似的扩展机制来支持其他证书格式和吊销状态信息格式，而无需对 CMS 进行进一步更改。 这些扩展主要记录在第 10.2.1 和 10.2.2 节中。 保留了与 CMS 早期版本的向后兼容性。

版本号的使用在第 1.3 节中描述。

自 RFC 3369 发布以来，已注意到一些勘误表。 这些勘误表发布在 RFC 编辑器网站上。 这些错误已在本文档中得到纠正。

11.4 节中描述反签名无符号属性的文本得到了澄清。 希望修订后的文本能够更清楚地了解 SignerInfo 签名中副署所涵盖的部分。

#### 1.1.4. 自 RFC 3852 以来的变化

本文档废弃 RFC 3852 [CMS3]。 发布本文档的主要原因是沿着标准成熟度阶梯推进 CMS。

本文档包含最初在 RFC 4853 [CMSMSIG] 中发布的有关在存在多个数字签名时正确处理 SignedData 受保护内容类型的说明。

自 RFC 3852 发布以来，已注意到一些勘误表。 这些勘误表发布在 RFC 编辑器网站上。 这些错误已在本文档中得到纠正。

### 1.2. 术语

在本文档中，关键字“必须”、“不得”、“必需”、“应该”、“不应该”、“推荐”、“可以”和“可选”应按 [STDWORDS] 中的描述进行解释。

### 1.3. 版本号

每个主要数据结构都包括版本号作为数据结构中的第一项。 版本号旨在避免 ASN.1 解码错误。 一些实现在尝试解码之前不检查版本号，并且如果发生解码错误，则检查版本号作为错误处理例程的一部分。 这是一个合理的做法； 它将错误处理置于快速路径之外。 当发送者使用不正确的版本号时，这种方法也是宽容的。

大多数初始版本号是在 PKCS #7 版本 1.5 中分配的。 其他人是在结构最初创建时分配的。 每当更新结构时，都会分配更高的版本号。 但是，为了确保最大程度的互操作性，仅在采用新语法功能时才使用更高的版本号。 也就是说，使用支持生成的语法的最低版本号。

## 2. 总体概述

CMS 足够通用，可以支持许多不同的内容类型。 该文档定义了一种保护内容ContentInfo。 ContentInfo封装单个识别的内容类型，并且识别的类型可以提供进一步的封装。 本文档定义了六种内容类型：数据、签名数据、封装数据、摘要数据、加密数据和认证数据。 可以在本文档之外定义其他内容类型。

符合此规范的实现必须实现保护内容 ContentInfo，并且必须实现数据、签名数据和封装数据内容类型。 可以实现其他内容类型。

作为一般设计理念，每种内容类型都允许使用不定长度基本编码规则 (BER) 编码进行单遍处理。 如果内容很大、存储在磁带上或从另一个进程“通过管道传输”，单遍操作尤其有用。 单遍操作有一个显着的缺点：很难在单遍中使用杰出编码规则（DER）[X.509-88]编码来执行编码操作，因为可能事先不知道各个分量的长度。 然而，签名数据内容类型内的签名属性和认证数据内容类型内的认证属性需要以 DER 形式传输，以确保接收者可以验证包含一个或多个未识别属性的内容。 签名属性和经过身份验证的属性是 CMS 中使用的唯一需要 DER 编码的数据类型。

## 3. 一般语法

以下对象标识符标识内容信息类型：

    id-ct-contentInfo OBJECT IDENTIFIER ::= { iso(1) member-body(2)
        us(840) rsadsi(113549) pkcs(1) pkcs9(9) smime(16) ct(1) 6 }

CMS 将内容类型标识符与内容相关联。 语法必须具有 ASN.1 类型 ContentInfo：

    ContentInfo ::= SEQUENCE {
        contentType ContentType,
        content [0] EXPLICIT ANY DEFINED BY contentType }

    ContentType ::= OBJECT IDENTIFIER

ContentInfo各字段含义如下：

    contentType 指示关联内容的类型。 它是一个对象标识符； 它是由定义内容类型的权威机构分配的唯一整数字符串。

    content是关联的内容。 content的类型可以通过contentType唯一确定。 本文档中定义了数据、签名数据、封装数据、摘要数据、加密数据和认证数据的内容类型。 如果在其他文档中定义了其他内容类型，则定义的 ASN.1 类型不应该是 CHOICE 类型。

## 4. Data Content Type

以下对象标识符标识数据内容类型：

    id-data OBJECT IDENTIFIER ::= { iso(1) member-body(2)
        us(840) rsadsi(113549) pkcs(1) pkcs7(7) 1 }

数据内容类型(Data Content Type)旨在引用任意八位字节字符串，例如 ASCII 文本文件； 解释留给应用程序。 此类字符串不需要具有任何内部结构（尽管它们可以具有自己的 ASN.1 定义或其他结构）。

S/MIME 使用 id-data 来识别 MIME 编码的内容。 此内容标识符的使用在 S/MIME v2 [MSG2] 的 RFC 2311、S/MIME v3 [MSG3] 的 RFC 2633 和 S/MIME v3.1 [MSG3.1] 的 RFC 3851 中指定。

## 5. 签名数据内容类型(Signed-data Content Type)

签名数据内容类型(Signed-data Content Type)由任意类型的内容和零个或多个签名值组成。 任意数量的并行签名者可以对任何类型的内容进行签名。

签名数据内容类型的典型应用表示一个签名者对该数据内容类型的内容的数字签名。 另一个典型的应用程序传播证书和证书吊销列表（CRL）。

构建签名数据的过程涉及以下步骤：

1. 对于每个签名者，使用签名者特定的消息摘要算法对内容计算消息摘要或哈希值。 如果签名者正在签署内容以外的任何信息，则内容的消息摘要和其他信息将使用签名者的消息摘要算法进行摘要（请参阅第 5.4 节），结果成为“消息摘要”。

2. 对于每个签名者，使用签名者的私钥对消息摘要进行数字签名。

3. 对于每个签名者，签名值和其他特定于签名者的信息被收集到 SignerInfo 值中，如第 5.3 节中所定义。 在此步骤中收集每个签名者以及不对应于任何签名者的证书和 CRL。

4. 所有签名者的消息摘要算法和所有签名者的 SignerInfo 值与内容一起收集到 SignedData 值中，如第 5.1 节中所定义。

接收者独立计算消息摘要。 该消息摘要和签名者的公钥用于验证签名值。 签名者的公钥可以通过两种方式之一引用。 可以通过颁发者可分辨名称以及颁发者特定的序列号来引用它，以唯一标识包含公钥的证书。 或者，它可以由主题密钥标识符引用，该标识符容纳经过认证的和未经认证的公钥。 虽然不是必需的，但签名者的证书可以包含在 SignedData 证书字段中。 当存在多个签名时，与给定签名者关联的一个签名的成功验证通常被视为该签名者的成功签名。 然而，有些应用环境需要其他规则。 如果应用程序对每个签名者采用的规则不是一个有效签名，则必须指定这些规则。 此外，在签名者标识符的简单匹配不足以确定签名是否由同一签名者生成的情况下，应用程序规范必须描述如何确定哪些签名是由同一签名者生成的。 不同收件人社区的支持是签名者选择包含多个签名的主要原因。 例如，签名数据内容类型可能包括使用 RSA 签名算法和椭圆曲线数字签名算法 (ECDSA) 签名算法生成的签名。 这允许接收者验证与一种算法或另一种算法相关联的签名。

本节分为六个部分。 第一部分描述顶级类型SignedData，第二部分描述EncapsulatedContentInfo，第三部分描述每个签名者信息类型SignerInfo，第四、第五和第六部分描述消息摘要计算、签名生成和签名验证 分别处理。

### 5.1. 签名数据类型(SignedData Type)

以下对象标识符标识签名数据内容类型：

    id-signedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
        us(840) rsadsi(113549) pkcs(1) pkcs7(7) 2 }

签名数据内容类型(signed-data content type)应具有 ASN.1 类型 SignedData：

SignedData ::= SEQUENCE {
    version CMSVersion,
    digestAlgorithms DigestAlgorithmIdentifiers,
    encapContentInfo EncapsulatedContentInfo,
    certificates [0] IMPLICIT CertificateSet OPTIONAL,
    crls [1] IMPLICIT RevocationInfoChoices OPTIONAL,
    signerInfos SignerInfos }

    DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier

    SignerInfos ::= SET OF SignerInfo

SignedData 类型的字段具有以下含义：

version 是语法版本号。 适当的值取决于证书、eContentType 和 SignerInfo。 版本必须按如下方式分配：

    IF ((certificates is present) AND
    (any certificates with a type of other are present)) OR
    ((crls is present) AND
    (any crls with a type of other are present))
    THEN version MUST be 5
    ELSE
    IF (certificates is present) AND
        (any version 2 attribute certificates are present)
    THEN version MUST be 4
    ELSE
        IF ((certificates is present) AND
            (any version 1 attribute certificates are present)) OR
            (any SignerInfo structures are version 3) OR
            (encapContentInfo eContentType is other than id-data)
        THEN version MUST be 3
        ELSE version MUST be 1

    IF（（存在证书）并且
    （存在任何具有其他类型的证书））或
    ((crls 存在) AND
    （存在任何具有其他类型的 crl））
    那么版本必须是 5
    ELSE
    IF（存在证书）AND
        （存在任何版本 2 属性证书）
    那么版本必须是 4
    ELSE
        IF（（存在证书）AND
            （存在任何版本 1 属性证书））或
            （任何 SignerInfo 结构均为版本 3）或
            （encapContentInfo eContentType 不是 id-data）
        THEN 版本必须是 3
        ELSE 版本必须为 1

digestAlgorithms 是消息摘要算法标识符的集合。 集合中可以有任意数量的元素，包括零。 每个元素标识一个或多个签名者使用的消息摘要算法以及任何相关参数。 该集合旨在以任意顺序列出所有签名者使用的消息摘要算法，以促进一次性签名验证。 实现可能无法验证使用不包含在此集合中的摘要算法的签名。 消息摘要过程在 5.4 节中描述。

encapContentInfo 是签名内容，由内容类型标识符和内容本身组成。 EncapsulatedContentInfo 类型的详细信息将在第 5.2 节中讨论。

certificates是证书的集合。 该组证书旨在足以包含从公认的“根”或“顶级证书颁发机构”到signerInfos 字段中的所有签名者的证书路径。 证书的数量可能多于必要的数量，并且可能有足以包含来自两个或更多独立顶级证书颁发机构的证书路径的证书。 如果预计接收者有其他方法来获取必要的证书（例如，从先前的一组证书），则证书的数量也可能少于所需的数量。 可以包括签名者的证书。 强烈建议不要使用版本 1 属性证书。

crls 是撤销状态信息的集合。 该集合的目的是包含足以确定证书字段中的证书是否有效的信息，但这种对应关系不是必需的。 证书吊销列表 (CRL) 是吊销状态信息的主要来源。 CRL 的数量可能多于必要的数量，并且 CRL 的数量也可能少于必要的数量。

SignerInfos 是每个签名者信息的集合。 集合中可以有任意数量的元素，包括零。 当该集合代表多个签名时，来自给定签名者的签名之一的成功验证应被视为该签名者的成功签名。 然而，有些应用环境需要其他规则。 SignerInfo 类型的详细信息将在第 5.3 节中讨论。 由于每个签名者可以采用不同的数字签名技术，并且未来的规范可能会更新语法，因此所有实现都必须妥善处理 SignerInfo 的未实现版本。 此外，由于并非所有实现都支持每种可能的签名算法，因此所有实现都必须在遇到未实现的签名算法时优雅地处理它们。

### 5.2. 封装内容信息类型(EncapsulatedContentInfo Type)

内容以 EncapsulatedContentInfo 类型表示：

    EncapsulatedContentInfo ::= SEQUENCE {
        eContentType ContentType,
        eContent [0] EXPLICIT OCTET STRING OPTIONAL }

    ContentType ::= OBJECT IDENTIFIER

EncapsulatedContentInfo 类型的字段具有以下内容：

eContentType 是一个对象标识符。 对象标识符唯一指定内容类型。

eContent 是内容本身，以八位字节字符串形式传送。 电子内容无需进行 DER 编码。

EncapsulatedContentInfo 字段中 eContent 的可选省略使得构建“外部签名”成为可能。 对于外部签名，签名数据内容类型中包含的 EncapsulatedContentInfo 值中不存在正在签名的内容。 如果EncapsulatedContentInfo中的eContent值不存在，则计算signatureValue并分配eContentType，就好像eContent值存在一样。

在没有签名者的退化情况下，“签名”的 EncapsulatedContentInfo 值是无关紧要的。 在这种情况下，“签名”的 EncapsulatedContentInfo 值中的内容类型必须是 id-data（如第 4 节中定义），并且必须省略 EncapsulatedContentInfo 值的内容字段。

#### 5.2.1. 与 PKCS #7 的兼容性

本节包含对希望支持 CMS 和 PKCS #7 [PKCS#7] SignedData 内容类型的实施者的警告。 CMS 和 PKCS #7 都使用对象标识符来标识封装内容的类型，但内容本身的 ASN.1 类型在 PKCS #7 SignedData 内容类型中是可变的。

PKCS #7 将内容定义为：

     content [0] EXPLICIT ANY DEFINED BY contentType OPTIONAL

CMS 将 eContent 定义为：

    eContent [0] EXPLICIT OCTET STRING OPTIONAL

CMS 定义在大多数应用程序中更易于使用，并且与 S/MIME v2 和 S/MIME v3 兼容。 使用 CMS 和 PKCS #7 的 S/MIME 签名消息是兼容的，因为在 RFC 2311（针对 S/MIME v2 [MSG2]）、RFC 2633（针对 S/MIME v3 [MSG3]）和 RFC 3851（针对 S/MIME v2）中指定了相同的签名消息格式。 MIME v3.1 [MSG3.1]。 S/MIME v2将MIME内容封装在SignedData contentInfo content ANY字段中携带的Data类型（即OCTET STRING）中，S/MIME v3将MIME内容携带在SignedData encapContentInfo eContent OCTET STRING中。 因此，在 S/MIME v2、S/MIME v3 和 S/MIME v3.1 中，MIME 内容放置在 OCTET STRING 中，并根据内容的相同部分计算消息摘要。 也就是说，消息摘要是在包含 OCTET STRING 值的八位位组上计算的，既不包括标签也不包括长度八位位组。

当封装内容未使用数据类型进行格式化时，CMS 和 PKCS #7 SignedData 类型之间存在不兼容性。 例如，当 RFC 2634 签名收据 [ESS] 封装在 CMS SignedData 类型中时，收据序列将编码在 SignedData encapContentInfo eContent OCTET STRING 中，并且使用整个收据序列编码（包括标签、长度）来计算消息摘要。 和值八位位组）。 但是，如果 RFC 2634 签名收据封装在 PKCS #7 SignedData 类型中，则收据序列在 SignedData contentInfo content ANY 字段中采用 DER 编码 [X.509-88]（序列，而不是 OCTET STRING）。 因此，仅使用收据序列编码的值八位位组来计算消息摘要。

在处理 SignedData 内容类型时，可以使用以下策略来实现与 PKCS #7 的向后兼容性。 如果实现无法使用 CMS SignedData encapContentInfo eContent OCTET STRING 语法对 SignedData 类型进行 ASN.1 解码，则实现可以尝试使用 PKCS #7 SignedData contentInfo content ANY 语法对 SignedData 类型进行解码，并相应地计算消息摘要。

在创建 SignedData 内容类型（其中封装的内容未使用数据类型进行格式化）时，可以使用以下策略来实现与 PKCS #7 的向后兼容性。 实现可以检查 eContentType 的值，然后根据对象标识符值调整 eContent 的预期 DER 编码。 例如，为了支持 Microsoft Authenticode [MSAC]，可以包含以下信息：

    eContentType Object Identifier is set to { 1 3 6 1 4 1 311 2 1 4 }

    eContent contains DER-encoded Authenticode signing information

### 5.3. 签名者信息类型(signerInfo Type)

每个签名者的信息以 SignerInfo 类型表示：

SignerInfo ::= SEQUENCE {
    version CMSVersion,
    sid SignerIdentifier,
    digestAlgorithm DigestAlgorithmIdentifier,
    signedAttrs [0] IMPLICIT SignedAttributes OPTIONAL,
    signatureAlgorithm SignatureAlgorithmIdentifier,
    signature SignatureValue,
    unsignedAttrs [1] IMPLICIT UnsignedAttributes OPTIONAL }

    SignerIdentifier ::= CHOICE {
        issuerAndSerialNumber IssuerAndSerialNumber,
        subjectKeyIdentifier [0] SubjectKeyIdentifier }

    SignedAttributes ::= SET SIZE (1..MAX) OF Attribute

    UnsignedAttributes ::= SET SIZE (1..MAX) OF Attribute

    Attribute ::= SEQUENCE {
        attrType OBJECT IDENTIFIER,
        attrValues SET OF AttributeValue }

    AttributeValue ::= ANY

    SignatureValue ::= OCTET STRING

SignerInfo 类型的字段具有以下含义：

version 是语法版本号。 如果 SignerIdentifier 是 CHOICE IssuerAndSerialNumber，则版本必须为 1。如果 SignerIdentifier 是 subjectKeyIdentifier，则版本必须为 3。

sid 指定签名者的证书（以及签名者的公钥）。 接收者需要签名者的公钥来验证签名。 SignerIdentifier 提供了两种指定签名者公钥的替代方法。 IssuerAndSerialNumber 替代方案通过颁发者的可分辨名称和证书序列号来标识签名者的证书； subjectKeyIdentifier 通过密钥标识符来标识签名者的证书。 当引用 X.509 证书时，密钥标识符与 X.509 subjectKeyIdentifier 扩展值匹配。 当引用其他证书格式时，指定证书格式及其与 CMS 的使用的文档必须包含有关将密钥标识符与相应证书字段相匹配的详细信息。 实现必须支持接收 SignerIdentifier 的 IssuerAndSerialNumber 和 subjectKeyIdentifier 形式。 当生成 SignerIdentifier 时，实现可以支持其中一种形式（issuerAndSerialNumber 或 subjectKeyIdentifier）并始终使用它，或者实现可以任意混合这两种形式。 然而，subjectKeyIdentifier 必须用于引用非 X.509 证书中包含的公钥。

digestAlgorithm 标识签名者使用的消息摘要算法以及任何关联的参数。 消息摘要是根据正在签名的内容或内容计算的

以及使用第 5.4 节中描述的过程的签名属性。 消息摘要算法应该在相关 SignerData 的digestAlgorithms 字段中列出的算法中。 实现可能无法验证使用未包含在 SignedData 摘要算法集中的摘要算法的签名。

signedAttrs 是已签名属性的集合。 该字段是可选的，但如果正在签名的 EncapsulatedContentInfo 值的内容类型不是 id-data，则该字段必须存在。 SignedAttributes 必须是 DER 编码的，即使结构的其余部分是 BER 编码的。 有用的属性类型，例如签名时间，在第 11 节中定义。如果该字段存在，则它必须至少包含以下两个属性：

     内容类型属性，其值是被签名的 EncapsulatedContentInfo 值的内容类型。 11.1 节定义了内容类型属性。 然而，内容类型属性不得用作第 11.4 节中定义的副署无符号属性的一部分。

     消息摘要属性，其值是内容的消息摘要。 11.2 节定义了消息摘要属性。

signatureAlgorithm 标识签名者用来生成数字签名的签名算法以及任何相关参数。

signature 是使用消息摘要和签名者的私钥生成数字签名的结果。 签名的细节取决于所使用的签名算法。

unsignedAttrs 是未签名的属性的集合。 该字段是可选的。 有用的属性类型，例如副署，在第 11 节中定义。

SignedAttribute 和 UnsignedAttribute 类型的字段具有以下含义：

attrType 表示属性的类型。 它是一个对象标识符。

attrValues 是组成属性的一组值。 集合中每个值的类型可以通过 attrType 唯一确定。 attrType 可以对集合中的项目数量施加限制。

### 5.4. 消息摘要计算过程

消息摘要计算过程对正在签名的内容或内容与签名的属性一起计算消息摘要。 无论哪种情况，消息摘要计算过程的初始输入都是正在签名的封装内容的“值”。 具体来说，初始输入是应用签名过程的 encapContentInfo eContent OCTET STRING。 仅包含 eContent OCTET STRING 值的八位位组被输入到消息摘要算法，而不是标签或长度八位位组。

消息摘要计算过程的结果取决于signedAttrs字段是否存在。 当该字段不存在时，结果只是如上所述的内容的消息摘要。 然而，当该字段存在时，结果是signedAttrs 字段中包含的SignedAttrs 值的完整DER 编码的消息摘要。 由于 SignedAttrs 值（如果存在）必须包含内容类型和消息摘要属性，因此这些值会间接包含在结果中。 内容类型属性不得包含在第 11.4 节中定义的副署无符号属性中。 对signedAttrs 字段进行单独编码以进行消息摘要计算。 signedAttrs 中的 IMPLICIT [0] 标签不用于 DER 编码，而是使用 EXPLICIT SET OF 标签。 也就是说，EXPLICIT SET OF 标记的 DER 编码（而不是 IMPLICIT [0] 标记）必须与 SignedAttributes 值的长度和内容八位字节一起包含在消息摘要计算中。

当signedAttrs字段不存在时，仅包含SignedData encapContentInfo eContent OCTET STRING的值的八位位组（例如，文件的内容）被输入到消息摘要计算。 这样做的优点是在签名生成过程之前不需要知道被签名的内容的长度。

尽管 encapContentInfo eContent OCTET STRING 标记和长度八位位组不包含在消息摘要计算中，但它们受到其他方式的保护。 长度八位位组受到消息摘要算法的性质的保护，因为在计算上不可能找到具有相同消息摘要的任何长度的任何两个不同的消息内容。

### 5.5. 签名生成过程

签名生成过程的输入包括消息摘要计算过程的结果和签名者的私钥。 签名生成的细节取决于所使用的签名算法。 对象标识符以及指定签名者所使用的签名算法的任何参数都包含在signatureAlgorithm 字段中。 签名者生成的签名值必须编码为八位字节字符串并携带在签名字段中。

### 5.6. 签名验证流程

签名验证过程的输入包括消息摘要计算过程的结果和签名者的公钥。 接收者可以通过任何方式为签名者获取正确的公钥，但首选方法是通过从 SignedData 证书字段获取的证书。 签名者公钥的选择和验证可以基于证书路径验证（请参阅[PROFILE]）以及其他外部上下文，但这超出了本文档的范围。 签名验证的细节取决于所使用的签名算法。

接收者不得依赖于发送者计算的任何消息摘要值。 如果 SignedData 签名者信息包含signedAttributes，那么内容消息摘要必须按照第 5.4 节中的描述进行计算。 为了使签名有效，接收者计算的消息摘要值必须与 SignedData 签名者信息的signedAttributes 中包含的messageDigest 属性的值相同。

如果 SignedData signerInfo 包含signedAttributes，则内容类型属性值必须与 SignedData encapContentInfo eContentType 值匹配。

## 6. 封装数据内容类型

封装数据内容类型由任何类型的加密内容和一个或多个接收者的加密内容加密密钥组成。 加密内容和接收者的一个加密内容加密密钥的组合是该接收者的“数字信封”。 使用每个接收者支持的任何密钥管理技术，可以为任意数量的接收者封装任何类型的内容。

封装数据内容类型的典型应用将表示数据或签名数据内容类型的内容上的一个或多个接收者的数字信封。

封装数据通过以下步骤构建：

1.特定内容加密算法的内容加密密钥是随机生成的。

2. 内容加密密钥针对每个接收者进行加密。 详细信息

此加密的效果取决于所使用的密钥管理算法，但支持四种通用技术：

    密钥传输：内容加密密钥在接收者的公钥中加密；

    密钥协商：使用接收方的公钥和发送方的私钥生成成对对称密钥，然后在成对对称密钥中对内容加密密钥进行加密；

    对称密钥加密密钥：内容加密密钥在先前分发的对称密钥加密密钥中加密； 和

    密码：内容加密密钥在从密码或其他共享秘密值派生的密钥加密密钥中进行加密。

3. 对于每个接收者，加密的内容加密密钥和其他特定于接收者的信息被收集到第 6.2 节中定义的 RecipientInfo 值中。

4. 使用内容加密密钥对内容进行加密。 内容加密可能需要将内容填充到某个块大小的倍数； 参见第 6.3 节。

5. 所有收件人的 RecipientInfo 值与加密内容一起收集，形成第 6.1 节中定义的 EnvelopedData 值。

接收者通过解密加密的内容加密密钥之一并且然后用恢复的内容加密密钥解密加密的内容来打开数字信封。

本节分为四个部分。 第一部分描述顶级类型 EnvelopedData，第二部分描述每个接收者信息类型 RecipientInfo，第三部分和第四部分描述内容加密和密钥加密过程。

6.1. 封装数据类型(EnvelopedData Type)

以下对象标识符标识封装数据内容类型：

    id-envelopedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
        us(840) rsadsi(113549) pkcs(1) pkcs7(7) 3 }

The enveloped-data content type shall have ASN.1 type EnvelopedData:

    EnvelopedData ::= SEQUENCE {
        version CMSVersion,
        originatorInfo [0] IMPLICIT OriginatorInfo OPTIONAL,
        recipientInfos RecipientInfos,
        encryptedContentInfo EncryptedContentInfo,
        unprotectedAttrs [1] IMPLICIT UnprotectedAttributes OPTIONAL }

    OriginatorInfo ::= SEQUENCE {
        certs [0] IMPLICIT CertificateSet OPTIONAL,
        crls [1] IMPLICIT RevocationInfoChoices OPTIONAL }

    RecipientInfos ::= SET SIZE (1..MAX) OF RecipientInfo

    EncryptedContentInfo ::= SEQUENCE {
        contentType ContentType,
        contentEncryptionAlgorithm ContentEncryptionAlgorithmIdentifier,
        encryptedContent [0] IMPLICIT EncryptedContent OPTIONAL }

    EncryptedContent ::= OCTET STRING

    UnprotectedAttributes ::= SET SIZE (1..MAX) OF Attribute

The fields of type EnvelopedData have the following meanings:

    version is the syntax version number.  The appropriate value depends on originatorInfo, RecipientInfo, and unprotectedAttrs.  The version MUST be assigned as follows:

        IF (originatorInfo is present) AND
        ((any certificates with a type of other are present) OR
        (any crls with a type of other are present))
        THEN version is 4
        ELSE
        IF ((originatorInfo is present) AND
            (any version 2 attribute certificates are present)) OR
            (any RecipientInfo structures include pwri) OR
            (any RecipientInfo structures include ori)
        THEN version is 3
        ELSE
            IF (originatorInfo is absent) AND
                (unprotectedAttrs is absent) AND
                (all RecipientInfo structures are version 0)
            THEN version is 0
            ELSE version is 2

originatorInfo 可选地提供有关发起者的信息。 仅当密钥管理算法需要时它才存在。 它可能包含证书和 CRL：

    certs 是证书的集合。 证书可能包含与几种不同的密钥管理算法关联的发起者证书。 证书还可以包含与发起者相关联的属性证书。 certs 中包含的证书足以让所有接收者从公认的“根”或“顶级证书颁发机构”构建证书路径。 但是，证书可能包含不必要的证书，并且可能有足够的证书来建立来自两个或更多独立顶级证书颁发机构的证书路径。 或者，如果预计接收者有其他方法来获取必要的证书（例如，从先前的一组证书），则证书可能包含比所需更少的证书。

    crls 是 CRL 的集合。 该集合旨在包含足以确定 certs 字段中的证书是否有效的信息，但这种对应关系不是必需的。 CRL 的数量可能多于必要的数量，并且 CRL 的数量也可能少于必要的数量。

recipientInfos (收件人信息)是每个收件人信息的集合。 集合中必须至少有一个元素。

cryptoContentInfo是加密的内容信息。

unprotectedAttrs 是未加密的属性的集合。 该字段是可选的。 有用的属性类型在第 11 节中定义。

EncryptedContentInfo 类型的字段具有以下含义：

contentType 表示内容的类型。

contentEncryptionAlgorithm 标识用于加密内容的内容加密算法以及任何关联的参数。 内容加密过程在第 6.3 节中描述。 相同的内容加密算法和内容加密密钥用于所有接收者。

加密内容是对内容进行加密的结果。 该字段是可选的，如果该字段不存在，则必须通过其他方式提供其预期值。
