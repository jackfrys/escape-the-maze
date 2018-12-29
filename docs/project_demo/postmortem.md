# Development Postmortem

## Rights
- We were able to collaborate effectively without meeting in person very often. We used Git and GitHub to manage our code while symultaneously working on different features. We messaged each other occasionally to plan what we would all work on, but we are all strong programmers who could contribute on our own time. Meetings at the beginning and end of the semester were necessary to set the project's direction and wrap up remaining work.
- We beat all of our deadlines. SDL development was easier to get going with than originally thought, so in all of our checkpoints we were able to complete all planned items, as well as several from the next milestone. The final project was feature complete a week before the deadline, with only a few fixes and refactoring remaining.

## Wrongs
- We did not implmement any unit tests until the end, so there was no way to verify the validity of the project after each commit without manually inspecting gameplay. We did have a CI build going for some time to check compilability, but it broke partway through after the Makefile was refactored. No test-driven development was employed.
- The code was not particularly well structured until some refactoring took place at the end. Because we worked in isolation, new features were added according to the programmer's style and taste, so at times it was hard to tell what was going on in some places. Fortunately, at the end we were able to clean some things up for improved readibility moving forward.