package models

import (
	"time"

	"github.com/google/uuid"
)

type TaskStatus string

const (
	TaskStatus_New        TaskStatus = "New"
	TaskStatus_InProgress TaskStatus = "InProgress"
	TaskStatus_Completed  TaskStatus = "Completed"
	TaskStatus_Invalid    TaskStatus = "Invalid"
)

// go reference time is 0 1 2 3 4 5 6 7 or 20060102150405
const timeFormat = "2006-01-02T15:04:05Z07:00"

type TaskInfo struct {
	ID                   string  `json:"id,omitempty"`
	InitialHoursEstimate float32 `json:"initialHoursEstimate,omitempty"`
	CurrentHoursEstimate float32 `json:"currentHoursEstimate,omitempty"`
	ActualHours          float32 `json:"actualHours,omitempty"`
	Description          string  `json:"description,omitempty"`
	CreatedAt            string  `json:"createdAt,omitempty"`
}

type Task struct {
	ID          string     `json:"id,omitempty"`
	SubTasks    []TaskInfo `json:"subTask,omitempty"`
	StoryPoints int        `json:"storyPoints,omitempty"`
	Title       string     `json:"title,omitempty"`
	Description string     `json:"description,omitempty"`
	Status      TaskStatus `json:"status,omitempty"`
	CreatedAt   string     `json:"createdAt,omitempty"`
}

func NewTask() Task {
	return Task{
		ID:        uuid.New().String(),
		Status:    TaskStatus_New,
		CreatedAt: time.Now().Format(timeFormat),
	}
}
