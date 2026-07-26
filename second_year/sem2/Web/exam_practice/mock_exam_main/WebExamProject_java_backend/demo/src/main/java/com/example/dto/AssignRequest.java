package com.example.dto;

import java.util.List;

public class AssignRequest {
    private String developerName;
    private List<String> projectNames;

    public String getDeveloperName() { return developerName; }
    public void setDeveloperName(String developerName) { this.developerName = developerName; }
    public List<String> getProjectNames() { return projectNames; }
    public void setProjectNames(List<String> projectNames) { this.projectNames = projectNames; }
}