package com.example.controller;

import com.example.model.SoftwareDeveloper;
import com.example.repository.SoftwareDeveloperRepository;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/developers")
@CrossOrigin(origins = "*")
public class SoftwareDeveloperController {

    private final SoftwareDeveloperRepository repo;

    public SoftwareDeveloperController(SoftwareDeveloperRepository repo) {
        this.repo = repo;
    }

    // GET /developers
    @GetMapping
    public List<SoftwareDeveloper> getAll() {
        return repo.findAll();
    }
}