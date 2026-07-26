package com.example.controller;

import com.example.dto.AssignRequest;
import com.example.model.Project;
import com.example.model.SoftwareDeveloper;
import com.example.repository.ProjectRepository;
import com.example.repository.SoftwareDeveloperRepository;
import org.springframework.web.bind.annotation.*;

import java.util.*;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/projects")
@CrossOrigin(origins = "*")
public class ProjectController {

    private final ProjectRepository projectRepo;
    private final SoftwareDeveloperRepository developerRepo;

    public ProjectController(ProjectRepository projectRepo, SoftwareDeveloperRepository developerRepo) {
        this.projectRepo = projectRepo;
        this.developerRepo = developerRepo;
    }

    // GET /projects
    @GetMapping
    public List<Project> getAllProjects() {
        return projectRepo.findAll();
    }

    // GET /projects/member/{name}
    @GetMapping("/member/{name}")
    public List<String> getProjectsByMember(@PathVariable String name) {
        return projectRepo.findAll().stream()
                .filter(p -> p.getMembers() != null && p.getMembers().toLowerCase().contains(name.toLowerCase()))
                .map(Project::getName)
                .collect(Collectors.toList());
    }

    // POST /projects/assign
    @PostMapping("/assign")
    public String assignDeveloperToProjects(@RequestBody AssignRequest req) {
        Optional<SoftwareDeveloper> devOpt = developerRepo.findByNameIgnoreCase(req.getDeveloperName());
        if (devOpt.isEmpty()) {
            return "Developer not found, nothing done.";
        }
        String devName = devOpt.get().getName();

        for (String projectName : req.getProjectNames()) {
            Optional<Project> projOpt = projectRepo.findByNameIgnoreCase(projectName.trim());

            Project project;
            if (projOpt.isEmpty()) {
                project = new Project();
                project.setName(projectName.trim());
                project.setMembers(devName);
                project.setProjectManagerId(devOpt.get().getId());
            } else {
                project = projOpt.get();
                String members = project.getMembers();
                if (members == null || members.isEmpty()) {
                    project.setMembers(devName);
                } else {
                    List<String> memberList = Arrays.stream(members.split(","))
                            .map(String::trim)
                            .collect(Collectors.toList());
                    if (!memberList.contains(devName)) {
                        project.setMembers(members + ", " + devName);
                    }
                }
            }
            projectRepo.save(project);
        }

        return "Developer assigned to projects successfully.";
    }
}