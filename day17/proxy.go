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