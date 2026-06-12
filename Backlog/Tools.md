# Tools
- [Powershell](#powershell)
- [Local LLM](#local-llm)

## Links <!-- omit from toc -->

## To Do <!-- omit from toc -->

## Powershell
- **Filename String Replace:**
  ```bash
  get-childitem * | foreach { rename-item -LiteralPath $_ $_.Name.Replace("Lecture ","") }
  ```

## Local LLM
- **llama.cpp:**
  - install using `winget install --id=ggml.llamacpp --exact --silent`
  - install [continue.dev](https://marketplace.visualstudio.com/items?itemName=Continue.continue) VS-Code extension
  - add below to `C:\Users\arun\.continue\config.yaml`
    ```yaml
    models:
      - name: llama.cpp
        provider: llama.cpp
        model: llama.cpp
        apiBase: http://localhost:8080
    ```
  - download model (GGUF version) from [Hugging Face](https://huggingface.co/models?num_parameters=min:0,max:6B&library=gguf&sort=downloads)
  - trigger llama.cpp server then use it in VS-Code
    ```bash
    llama-server -m <path_to_model>
    ```