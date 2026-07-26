package com.example.model;

import jakarta.persistence.*;

@Entity
@Table(name = "Project")
public class Project {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @Column(name = "ProjectManagerID")
    private Integer projectManagerId;

    private String name;
    private String description;
    private String members;

    // getters and setters
    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }
    public Integer getProjectManagerId() { return projectManagerId; }
    public void setProjectManagerId(Integer projectManagerId) { this.projectManagerId = projectManagerId; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
    public String getMembers() { return members; }
    public void setMembers(String members) { this.members = members; }
}