# Cryptographic Message Syntax

## 1. 通用格式

```asn1
ContentInfo ::= SEQUENCE {
    contentType ContentType,    # 指示后续的内容的类型，参见
                                # Content Type Object Identifiers章节
    content [0] EXPLICIT ANY DEFINED BY contentType }
                                # 根据ContentType确定后面的数据格式

    ContentType ::= OBJECT IDENTIFIER
```

## 2. SignedData (ContentType=pkcs7-signedData)

### 2.1 ContentType类型

**<font color=red>pkcs7-signedData (1.2.840.113549.1.7.2)</font>**

```asn1
  id-signedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 2 }
```

### 2.2 SignedData 

```asn1
# 主结构
SignedData ::= SEQUENCE {
    version CMSVersion,
    digestAlgorithms DigestAlgorithmIdentifiers,        # 1
    encapContentInfo EncapsulatedContentInfo,           # 2
    certificates [0] IMPLICIT CertificateSet OPTIONAL,  # 3
    crls [1] IMPLICIT RevocationInfoChoices OPTIONAL,   # 4
    signerInfos SignerInfos }                           # 5
```

#### 2.2.1 DigestAlgorithmIdentifiers

```asn1
    DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier

        DigestAlgorithmIdentifier ::= AlgorithmIdentifier
```

#### 2.2.2 EncapsulatedContentInfo

根据数据类型确定内容。比如：pkcs7-data

```asn1
    EncapsulatedContentInfo ::= SEQUENCE {
        eContentType ContentType,
        eContent [0] EXPLICIT OCTET STRING OPTIONAL }
```

```asn1
    SignerInfos ::= SET OF SignerInfo

        SignerInfo ::= SEQUENCE {
            version CMSVersion,
            sid SignerIdentifier,
            digestAlgorithm DigestAlgorithmIdentifier,
            signedAttrs [0] IMPLICIT SignedAttributes OPTIONAL,
            signatureAlgorithm SignatureAlgorithmIdentifier,
            signature SignatureValue,
            unsignedAttrs [1] IMPLICIT UnsignedAttributes OPTIONAL }
```

```asn1
            SignerIdentifier ::= CHOICE {
                issuerAndSerialNumber IssuerAndSerialNumber,
                subjectKeyIdentifier [0] SubjectKeyIdentifier }

            DigestAlgorithmIdentifier ::= AlgorithmIdentifier

            SignedAttributes ::= SET SIZE (1..MAX) OF Attribute

            UnsignedAttributes ::= SET SIZE (1..MAX) OF Attribute

                Attribute ::= SEQUENCE {
                    attrType OBJECT IDENTIFIER,
                    attrValues SET OF AttributeValue }

                    AttributeValue ::= ANY

            SignatureValue ::= OCTET STRING
```

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

        RecipientInfo ::= CHOICE {
            ktri KeyTransRecipientInfo,
            kari [1] KeyAgreeRecipientInfo,
            kekri [2] KEKRecipientInfo,
            pwri [3] PasswordRecipientInfo,
            ori [4] OtherRecipientInfo }

    EncryptedKey ::= OCTET STRING

            KeyTransRecipientInfo ::= SEQUENCE {
                version CMSVersion,  -- always set to 0 or 2
                rid RecipientIdentifier,
                keyEncryptionAlgorithm KeyEncryptionAlgorithmIdentifier,
                encryptedKey EncryptedKey }

                RecipientIdentifier ::= CHOICE {
                    issuerAndSerialNumber IssuerAndSerialNumber,
                    subjectKeyIdentifier [0] SubjectKeyIdentifier }

            KeyAgreeRecipientInfo ::= SEQUENCE {
                version CMSVersion,  -- always set to 3
                originator [0] EXPLICIT OriginatorIdentifierOrKey,
                ukm [1] EXPLICIT UserKeyingMaterial OPTIONAL,
                keyEncryptionAlgorithm KeyEncryptionAlgorithmIdentifier,
                recipientEncryptedKeys RecipientEncryptedKeys }

                OriginatorIdentifierOrKey ::= CHOICE {
                    issuerAndSerialNumber IssuerAndSerialNumber,
                    subjectKeyIdentifier [0] SubjectKeyIdentifier,
                    originatorKey [1] OriginatorPublicKey }

                    OriginatorPublicKey ::= SEQUENCE {
                        algorithm AlgorithmIdentifier,
                        publicKey BIT STRING }

                RecipientEncryptedKeys ::= SEQUENCE OF RecipientEncryptedKey

                    RecipientEncryptedKey ::= SEQUENCE {
                        rid KeyAgreeRecipientIdentifier,
                        encryptedKey EncryptedKey }

                        KeyAgreeRecipientIdentifier ::= CHOICE {
                            issuerAndSerialNumber IssuerAndSerialNumber,
                            rKeyId [0] IMPLICIT RecipientKeyIdentifier }

                            RecipientKeyIdentifier ::= SEQUENCE {
                                subjectKeyIdentifier SubjectKeyIdentifier,
                                date GeneralizedTime OPTIONAL,
                                other OtherKeyAttribute OPTIONAL }

                                SubjectKeyIdentifier ::= OCTET STRING

            KEKRecipientInfo ::= SEQUENCE {
                version CMSVersion,  -- always set to 4
                kekid KEKIdentifier,
                keyEncryptionAlgorithm KeyEncryptionAlgorithmIdentifier,
                encryptedKey EncryptedKey }

                KEKIdentifier ::= SEQUENCE {
                    keyIdentifier OCTET STRING,
                    date GeneralizedTime OPTIONAL,
                    other OtherKeyAttribute OPTIONAL }

            PasswordRecipientInfo ::= SEQUENCE {
                version CMSVersion,   -- always set to 0
                keyDerivationAlgorithm [0] KeyDerivationAlgorithmIdentifier
                                            OPTIONAL,
                keyEncryptionAlgorithm KeyEncryptionAlgorithmIdentifier,
                encryptedKey EncryptedKey }

        OtherRecipientInfo ::= SEQUENCE {
            oriType OBJECT IDENTIFIER,
            oriValue ANY DEFINED BY oriType }

DigestedData ::= SEQUENCE {
    version CMSVersion,
    digestAlgorithm DigestAlgorithmIdentifier,
    encapContentInfo EncapsulatedContentInfo,
    digest Digest }

    Digest ::= OCTET STRING

EncryptedData ::= SEQUENCE {
    version CMSVersion,
    encryptedContentInfo EncryptedContentInfo,
    unprotectedAttrs [1] IMPLICIT UnprotectedAttributes OPTIONAL }

AuthenticatedData ::= SEQUENCE {
    version CMSVersion,
    originatorInfo [0] IMPLICIT OriginatorInfo OPTIONAL,
    recipientInfos RecipientInfos,
    macAlgorithm MessageAuthenticationCodeAlgorithm,
    digestAlgorithm [1] DigestAlgorithmIdentifier OPTIONAL,
    encapContentInfo EncapsulatedContentInfo,
    authAttrs [2] IMPLICIT AuthAttributes OPTIONAL,
    mac MessageAuthenticationCode,
    unauthAttrs [3] IMPLICIT UnauthAttributes OPTIONAL }

    AuthAttributes ::= SET SIZE (1..MAX) OF Attribute

    UnauthAttributes ::= SET SIZE (1..MAX) OF Attribute

    MessageAuthenticationCode ::= OCTET STRING

    DigestAlgorithmIdentifier ::= AlgorithmIdentifier

    SignatureAlgorithmIdentifier ::= AlgorithmIdentifier

    KeyEncryptionAlgorithmIdentifier ::= AlgorithmIdentifier

    ContentEncryptionAlgorithmIdentifier ::= AlgorithmIdentifier

    MessageAuthenticationCodeAlgorithm ::= AlgorithmIdentifier

    KeyDerivationAlgorithmIdentifier ::= AlgorithmIdentifier

    RevocationInfoChoices ::= SET OF RevocationInfoChoice

        RevocationInfoChoice ::= CHOICE {
            crl CertificateList,
            other [1] IMPLICIT OtherRevocationInfoFormat }

        OtherRevocationInfoFormat ::= SEQUENCE {
            otherRevInfoFormat OBJECT IDENTIFIER,
            otherRevInfo ANY DEFINED BY otherRevInfoFormat }

CertificateChoices ::= CHOICE {
    certificate Certificate,
    extendedCertificate [0] IMPLICIT ExtendedCertificate,  -- Obsolete
    v1AttrCert [1] IMPLICIT AttributeCertificateV1,        -- Obsolete
    v2AttrCert [2] IMPLICIT AttributeCertificateV2,
    other [3] IMPLICIT OtherCertificateFormat }

    AttributeCertificateV2 ::= AttributeCertificate

    OtherCertificateFormat ::= SEQUENCE {
        otherCertFormat OBJECT IDENTIFIER,
        otherCert ANY DEFINED BY otherCertFormat }

CertificateSet ::= SET OF CertificateChoices

IssuerAndSerialNumber ::= SEQUENCE {
    issuer Name,
    serialNumber CertificateSerialNumber }

CMSVersion ::= INTEGER  { v0(0), v1(1), v2(2), v3(3), v4(4), v5(5) }

UserKeyingMaterial ::= OCTET STRING

OtherKeyAttribute ::= SEQUENCE {
    keyAttrId OBJECT IDENTIFIER,
    keyAttr ANY DEFINED BY keyAttrId OPTIONAL }

-- Content Type Object Identifiers

id-ct-contentInfo OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs9(9) smime(16) ct(1) 6 }

id-data OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 1 }

id-signedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 2 }

id-envelopedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 3 }

id-digestedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 5 }

id-encryptedData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs7(7) 6 }

id-ct-authData OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs-9(9) smime(16) ct(1) 2 }

-- The CMS Attributes

MessageDigest ::= OCTET STRING

SigningTime  ::= Time

Time ::= CHOICE {
    utcTime UTCTime,
    generalTime GeneralizedTime }

Countersignature ::= SignerInfo

-- Attribute Object Identifiers

id-contentType OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs9(9) 3 }

id-messageDigest OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs9(9) 4 }

id-signingTime OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs9(9) 5 }

id-countersignature OBJECT IDENTIFIER ::= { iso(1) member-body(2)
    us(840) rsadsi(113549) pkcs(1) pkcs9(9) 6 }

-- Obsolete Extended Certificate syntax from PKCS #6

ExtendedCertificateOrCertificate ::= CHOICE {
    certificate Certificate,
    extendedCertificate [0] IMPLICIT ExtendedCertificate }

ExtendedCertificate ::= SEQUENCE {
    extendedCertificateInfo ExtendedCertificateInfo,
    signatureAlgorithm SignatureAlgorithmIdentifier,
    signature Signature }

ExtendedCertificateInfo ::= SEQUENCE {
    version CMSVersion,
    certificate Certificate,
    attributes UnauthAttributes }

Signature ::= BIT STRING

END -- of CryptographicMessageSyntax2004


