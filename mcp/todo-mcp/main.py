import requests
from mcp.server.fastmcp import FastMCP, Context

mcp = FastMCP (
        "todo-mcp",
        host="localhost", 
        port=1234
    )

@mcp.tool()
async def get_all_schemas (context: Context):
    """
    List all schemas from the todo webserver.
    """

    response = requests.get ("http://localhost:1234/schemas")
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

@mcp.tool()
async def get_schema_by_type (context: Context, schema_type: str):
    """
    Get a specific schema by type from the todo webserver.
    """

    params = {"filter": schema_type}
    response = requests.get ("http://localhost:1234/schemas", params=params)
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}
    
@mcp.tool()
async def get_health_check (context: Context):
    """
    Perform a health check on the todo webserver.
    """

    response = requests.get ("http://localhost:1234/health")
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}
    
@mcp.tool()
async def shutdown_server (context: Context):
    """
    Shutdown the todo webserver.
    """

    body = {"command": "yes"}

    response = requests.post ("http://localhost:1234/shutdown", json=body)
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

@mcp.tool()
async def create_task (name: str, description: str, context: Context):
    """
    Create a new task in the todo webserver.
    """

    body = {
        "name": name,
        "description": description
    }

    response = requests.post ("http://localhost:1234/create", json=body)
    
    if response.status_code == 201:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

@mcp.tool()
async def list_tasks (context: Context):
    """
    List all tasks from the todo webserver.
    """

    response = requests.get ("http://localhost:1234/display")
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

@mcp.tool()
async def update_task (id: int, name: str, description: str, context: Context):
    """
    Update an existing task in the todo webserver.
    """

    body = {
        "id": id,
        "name": name,
        "description": description
    }

    response = requests.put ("http://localhost:1234/update", json=body)
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}
    
@mcp.tool()
async def delete_task (id: int, context: Context):
    """
    Delete a task from the todo webserver.
    """

    body = {
        "id": id
    }

    response = requests.delete ("http://localhost:1234/delete", json=body)
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

@mcp.tool()
async def mark_task_complete (id: int, context: Context):
    """
    Mark a task as complete in the todo webserver.
    """

    body = {
        "id": id
    }

    response = requests.post ("http://localhost:1234/complete", json=body)
    
    if response.status_code == 200:
        result = response.json()
        await context.info (str(result))
        return result
    else:
        error_msg = f"Error {response.status_code}: {response.text}"
        await context.error (error_msg)
        return {"error": error_msg}

if __name__ == "__main__":
    mcp.run (transport="stdio")
