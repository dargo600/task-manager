package handlers

import (
        "net/http"

        "github.com/gorilla/mux"
)

// ConfigureHandler configures the routes of this handler and binds handler functions to them
func ConfigureHandler(handler Handler) *mux.Router {
        router := mux.NewRouter().StrictSlash(true)

        router.Methods("GET").Path("/").Handler(http.HandlerFunc(handler.Index))
        router.Methods("GET").Path("/tasks/{taskId}").
                Handler(http.HandlerFunc(handler.TaskShow))
        router.Methods("POST").Path("/tasks").
                Handler(http.HandlerFunc(handler.TaskInsert))

        return router
}

