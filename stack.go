package main

type SNode struct {
    value string
    next  *SNode
}

type Stack struct {
    name string
    top  *SNode
}

func createStack(name string) *Stack {
    return &Stack{
        name: name,
        top:  nil,
    }
}

func (s *Stack) push(value string) {
    node := &SNode{value: value, next: s.top}
    s.top = node
}

func (s *Stack) pop() string {
    if s.top == nil {
        return ""
    }
    value := s.top.value
    s.top = s.top.next
    return value
}

func (s *Stack) peek() string {
    if s.top == nil {
        return ""
    }
    return s.top.value
}

func (s *Stack) read() string {
    result := ""
    cur := s.top
    for cur != nil {
        result += cur.value
        if cur.next != nil {
            result += " "
        }
        cur = cur.next
    }
    return result
}
