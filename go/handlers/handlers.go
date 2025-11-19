package handlers

import (
        "net/http"
        "sync"

        "github.com/dargo600/task-manager/go/repo"
        "github.com/gorilla/mux"
)

// handler holds all the dependencies required for server requests
type handler struct {
        repo repo.Repo
        once sync.Once
}

// Handler is the interface we expose to outside packages
type Handler interface {
        Index(w http.ResponseWriter, r *http.Request)
        TaskShow(w http.ResponseWriter, r *http.Request)
        TaskInsert(w http.ResponseWriter, r *http.Request)
}


func New() (Handler, error) {
    r, err := repo.New()
    if err != nil {
        return nil, err
    }
    h := handler{
        repo: r,
    }
    return &h, nil
}

// Index returns a simple welcome response for the homepage
func (h *handler) Index(w http.ResponseWriter, r *http.Request) {
	// Send an HTTP status & a hardcoded message
	writeResponse(w, http.StatusOK, "Welcome to the Tasks App!", nil)
}

// TaskShow fetches and displays one existing task
func (h *handler) TaskShow(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	taskId := vars["taskId"]
	// Call the repository method corresponding to the operation
	o, err := h.repo.GetTask(taskId)
	// Handle any errors & write an error HTTP status & response
	if err != nil {
		writeResponse(w, http.StatusNotFound, nil, err)
		return
	}
	// Send an HTTP success status & the return value from the repo
	writeResponse(w, http.StatusOK, o, nil)
}

// TaskInsert creates a new task with the given parameters
func (h *handler) TaskInsert(w http.ResponseWriter, r *http.Request) {
	task, err := h.repo.CreateTask()
	if err != nil {
		writeResponse(w, http.StatusInternalServerError, nil, err)
		return
	}
	writeResponse(w, http.StatusOK, task, nil)
}




