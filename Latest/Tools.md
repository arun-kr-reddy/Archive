# Tools
- [Git](#git)
  - [Init](#init)
  - [Basic Workflow](#basic-workflow)
  - [Branching](#branching)
  - [Remote](#remote)
  - [Undo \& Fix](#undo--fix)
  - [Stash](#stash)
  - [Tags](#tags)
  - [History](#history)
- [Mermaid](#mermaid)
  - [Flowchart](#flowchart)
  - [Sequence Diagram](#sequence-diagram)
  - [Gantt Diagram](#gantt-diagram)
  - [Class Diagram](#class-diagram)
  - [Git Graph](#git-graph)
  - [Quadrant Chart](#quadrant-chart)
  - [X-Y Chart](#x-y-chart)

## Links <!-- omit from toc -->
- [Git Commands Cheatsheet](https://www.reddit.com/r/git/comments/1oj159s/git_commands_cheat_sheet_what_should_i_add_or_fix/)
- [Git Documentation](https://git-scm.com/docs)
- [Mermaid Documentation](https://mermaid.js.org/intro/)

## Git

### Init
- 
  |                                                 |                                     |
  | ----------------------------------------------- | ----------------------------------- |
  | `git init`                                      | start new local repo                |
  | `git clone <url>`                               | clone repo from remote              |
  | `git clone --branch <branch> <url>`             | clone remote repo + checkout branch |
  | `git config --global core.editor "code --wait"` | use VS-Code as git editor           |

### Basic Workflow
- 
  |                      |                                                             |
  | -------------------- | ----------------------------------------------------------- |
  | `git status`         | check status of files (un-tracked, un-staged, un-committed) |
  | `git add <file>`     | stage file                                                  |
  | `git add -p`         | interactively review & stage every change hunk              |
  | `git commit`         | commit, but supports multi-line commit message              |
  | `git commit -v`      | commit + diff                                               |
  | `git commit --amend` | edit last commit                                            |
  | `git log`            | show commit history                                         |
  | `git log --oneline`  | pretty log view                                             |
  | `git diff`           | show un-staged changes                                      |
  | `git diff --staged`  | show staged diff                                            |
- `git add .`/`git add -A` discouraged to prevent accidently staging untracked files  
  `git commit -m <msg>` discouraged to write multi-line commit messages

### Branching
- 
  |                                   |                                    |
  | --------------------------------- | ---------------------------------- |
  | `git branch`                      | list branches                      |
  | `git branch <name>`               | create new branch                  |
  | `git switch <name>`, `git checkout <name>`               | switch to branch                   |
  | `git switch -c <name>`, `git checkout -b <name>`            | create branch + switch branch      |
  | `git merge <branch>`              | merge branch into current          |
  | `git rebase <branch>`             | rebase current onto another branch |
  | `git branch -d <name>`            | delete local branch                |
  | `git push --delete origin <name>` | delete remote branch               |
  | `git cherry-pick <commit>`        | apply specific commit              |
- `checkout` can used for files, commits, tags & branches, instead use modern `switch` & `restore`
- **Interactive Rebase:**
  - `git rebase -i HEAD~n` to modify last n commits
  - shows commits in oldest-to-newest order in the editor
    ```sh
    pick a1b2c3d Add feature
    pick e5f6g7h Fix typo
    pick i9j0k1l Actually fix typo
    ```
  - apply one of below action
    - `pick`: **(default)** keep commit as is
    - `reword`: keep commit but change log message
    - `edit`: amend files in that commit
    - `squash`: meld commit with one above it, and combine messages
    - `fixup`: like squash, but discards message
    - `drop`: deletes commit entirely
  - git starts executing actions once editor saved & exited
  - ***Example:* Squashing:** below actions will create one clean commit `"Add feature"`
    ```sh
    # after
    pick a1b2c3d Add feature
    fixup e5f6g7h Fix typo
    fixup i9j0k1l Actually fix typo
    ```

### Remote
- 
  |                               |                                            |
  | ----------------------------- | ------------------------------------------ |
  | `git remote -v`               | show remotes                               |
  | `git remote add origin <url>` | add remote origin (usually empty repo)     |
  | `git push -u origin main`     | push first time                            |
  | `git push`                    | push changes                               |
  | `git pull`                    | pull latest changes + merge local commits  |
  | `git pull --rebase`           | pull remote changes + rebase local commits |
  | `git fetch`                   | fetch branches/tags from default remote    |
  | `git fetch --prune`           | remove deleted remotes                     |
- `git pull` refuses to work with un-committed files, so stash them first

### Undo & Fix
- 
  |                                    |                                                          |
  | ---------------------------------- | -------------------------------------------------------- |
  | `git restore <file>`               | discard local changes in file                            |
  | `git reset <file>`                 | unstage a file, changes kept                             |
  | `git reset --hard`                 | reset to last commit                                     |
  | `git reset --hard <commit>`        | reset to commit                                          |
  | `git reset --hard origin/<branch>` | reset to remote branch                                   |
  | `git revert <commit>`              | new commit undoing old one                               |
  | `git reflog`                       | local-only recycle bin (lost commits) & history          |
  | `git clean -fd`                    | permanently delete untracked files & folders (no reflog) |
  | `git clean -nd`                    | dry run that lists untracked files                       |
  | `git clean -fdx`                   | delete untracked & ignored files                         |

### Stash
- 
  |                               |                           |
  | ----------------------------- | ------------------------- |
  | `git stash`                   | save un-committed changes |
  | `git stash pop`               | apply last stash          |
  | `git stash list`              | show stash list           |
  | `git stash apply 'stash@{n}'` | apply specific stash      |
  | `git stash drop 'stash@{n}'`  | remove specific stash     |

### Tags
- 
  |                          |                 |
  | ------------------------ | --------------- |
  | `git tag <tag>`          | create tag      |
  | `git tag`                | list tags       |
  | `git tag -d <tag>`       | delete tag      |
  | `git push origin <tag>`  | push single tag |
  | `git push origin --tags` | push all tags   |
  | `git checkout <tag>`     | checkout tag    |

### History
- 
  |                                |                                      |
  | ------------------------------ | ------------------------------------ |
  | `git show <commit>`            | show changes in specific commit      |
  | `git blame <file>`             | show which commit modified each line |
  | `git blame -L 50,60 <file>`    | blame for lines [50, 60]             |
  | `git blame -L 50,+10 <file>`   | blame for lines [50, 50+10]          |
  | `git blame -L :foo <file>`     | blame for lines in foo function      |
  | `git shortlog -sn`             | show num commits per author          |
  | `git log --since="2026-03-01"` | filter commits by date               |
  | `git log -p <file>`            | show file history with commit + diff |

## Mermaid

### Flowchart
- **Node Shapes:**
  |               |               |              |
  | ------------- | ------------- | ------------ |
  | oval          | `id1((text))` | start/end    |
  | parallelogram | `id1[/text/]` | input/output |
  | rectangle     | `id1[text]`   | process node |
  | diamond       | `id1{text}`   | decision     |
- ```text
  graph LR
      a((start))
      b[func1]
      c[func2]
      d[/input/]
      e{cond}
      f((end))

      a --> b
      b --> e
      c --> f
      e -- no --> f

      %% all nodes used in subgraph grouped together
      subgraph process
      e -- yes --> c
      d -. copy .-> c
      end
  ```
  ```mermaid
  graph LR
    a((start))
    b[func1]
    c[func2]
    d[/input/]
    e{cond}
    f((end))

    a --> b
    b --> e
    c --> f
    e -- no --> f

    subgraph subgroup
    e -- yes --> c
    d -. copy .-> c
    end
  ```

### Sequence Diagram
- ```text
  %% participants rendered in order of declaration
  sequenceDiagram
    title example sequence diagram
    autonumber  %% to auto-generate sequence numbers
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    %% activation period by appending + & - to connection
    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```
  ```mermaid
  sequenceDiagram
    title example sequence diagram
    autonumber
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```

### Gantt Diagram
- ```text
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```
  ```mermaid
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```

### Class Diagram
- **Relations:**
  |            |                   |
  | ---------- | ----------------- |
  | `<\|--`    | inheritance       |
  | `*--`      | composition       |
  | `o--`      | aggregation       |
  | `-->`      | association       |
  | `---`      | link              |
  | `..>`      | dependency        |
  | `..>`      | realization       |
  | `<\|--\|>` | two-way relations |
- ```text
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```
  ```mermaid
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```

### Git Graph
- ```text
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```
  ```mermaid
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```

### Quadrant Chart
- ```text
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    %% without points, quadrant titles in the centre
    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```
  ```mermaid
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```

### X-Y Chart
- ```text
  ---
  config:
    themeVariables:
      xyChart:
        plotColorPalette: '#000000, #FF0000, #00FF00'
  ---
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [20000, 100000, 400000, 2000000, 3000000, 5000000, 6000000, 7000000, 10000000, 12000000, 16000000, 18000000]
  ```
  ```mermaid
  ---
  config:
    themeVariables:
      xyChart:
        plotColorPalette: '#000000, #FF0000, #00FF00'
  ---
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9000000]
    line [20000, 100000, 400000, 2000000, 3000000, 5000000, 6000000, 7000000, 10000000, 12000000, 16000000, 18000000]
  ```