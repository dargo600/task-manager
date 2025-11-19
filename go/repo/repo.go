package repo

import (
	"fmt"
   
    "github.com/dargo600/task-manager/go/db"
    "github.com/dargo600/task-manager/go/models"
)

// repo holds all the dependencies required for repo operations
type repo struct {
	tasks     *db.TaskDB
	incoming  chan models.Task
	done      chan struct{}
	processed chan models.Task
}

type Repo interface {
	CreateTask() (*models.Task, error)
	GetTask(id string) (models.Task, error)
	Close()
}

func New() (Repo, error) {
    processed := make(chan models.Task)
	done := make(chan struct{})
	t := repo{
		tasks:     db.NewTasks(),
		incoming:  make(chan models.Task),
		done:      done,
        processed:   processed,
	}
	// start the task processor
	go t.processTasks()
	return &t, nil
}

// GetTask retrieves a task by it's ID if one exists
func (r *repo) GetTask(id string) (models.Task, error) {
    return r.tasks.Find(id)
}

// CreateTask creates a new task for the given item
func (r *repo) CreateTask() (*models.Task, error) {
	task := models.NewTask()
	// place the task on the incoming tasks channel
	select {
	case r.incoming <- task:
		r.tasks.Upsert(task)
		return &task, nil
	case <-r.done:
		return nil, fmt.Errorf("tasks app is closed, try again later")
	}
}

func (r *repo) processTasks() {
	fmt.Println("Task processing started!")
	for {
		select {
		case task := <-r.incoming:
			r.tasks.Upsert(task)
			fmt.Printf("Task %s added\n", task.ID)
			r.processed <- task
		case <-r.done:
			fmt.Println("Task processing stopped!")
			return
		}
	}
}

// Close closes the orders app for incoming orders
func (r *repo) Close() {
        close(r.done)
}

