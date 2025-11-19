package main

import (
        "fmt"
        "log"
        "net/http"

        "github.com/dargo600/task-manager/go/handlers"
)

func main() {
    fmt.Println("Starting Task Manager App...")
    handler, err := handlers.New()
    if err != nil {
        log.Fatal(err)
    }
    router := handlers.ConfigureHandler(handler)
    fmt.Println("Listening on 3001")
    log.Fatal(http.ListenAndServe(":3001", router))
}
