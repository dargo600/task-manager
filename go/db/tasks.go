package db

import(
	"fmt"
	"sync"

    "github.com/dargo600/task-manager/go/models"
)

type TaskDB struct {
	tasks sync.Map
}

// New Tasks creates a new empty task service
func NewTasks() *TaskDB {
	return &TaskDB{}
}

// Find task for a given id, if one exists
func (t *TaskDB) Find(id string) (models.Task, error) {
	pt, ok := t.tasks.Load(id)
	if !ok {
		return models.Task{}, fmt.Errorf("task with ID %s not found", id)
	}
	return toTask(pt), nil
}

// Upsert creates or updates a task in the tasks database
func (db *TaskDB) Upsert(task models.Task) (*models.Task, error) {
	db.tasks.Store(task.ID, task)
	return &task, nil
}

// toTask attempts to convert an interface to a task
// panics if this is not possible
func toTask(to interface{}) models.Task {
	task, ok := to.(models.Task)
	if !ok {
	    panic(fmt.Errorf("error casting %v to task", to))
	}
	return task
}
