import React, { Component } from 'react';
import logo from './assets/logo.png';
import './App.css';
import 'semantic-ui-css/semantic.min.css';
import {Input, Image, Header, Button, List, Icon, Modal} from 'semantic-ui-react'
import FileReaderInput from 'react-file-reader-input';

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      expression: '',
      value: '',
      isVariable: false,
      isDelete: false,
      isExport: false,
      isExiting: false,
      isModalOpen: false,
      current_var:'',
      vars: []
    };
  }

  handleAddVar = async () => {
    const { expression } = this.state;
    const nGROKendpoint = 'http://127.0.0.1:8080/addvar';
    await fetch(nGROKendpoint,
      { method: 'POST',
        headers: { 'content-type': 'text/plain' },
        body: expression
      }
    );

    this.setState({
      expression: ""
    });

    alert("expression is now stored in memory location <M>")

  }

  handleDelVar = async () => {
    const { expression } = this.state;
    const nGROKendpoint = 'http://127.0.0.1:8080/delvar';

    await fetch(nGROKendpoint,
      { method: 'POST',
        headers: { 'content-type': 'text/plain' },
        body: expression
      }
    );

    this.setState({
      expression: ""
    });

    alert("expression is now stored in memory location <M>")
  }

  handleGetVar = async () => {
    const nGROKendpoint = 'http://127.0.0.1:8080/getvar';
    const rawResponse = await fetch(nGROKendpoint,
      { method: 'POST',
	      headers: { 'content-type': 'text/plain' }
      }
    );

    const myJSON = JSON.parse(await rawResponse.text())
    let temp = []
    const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for(let i = 0; i < 26; i++)
      temp.push(myJSON[alphabet[i]])
    this.setState({
      vars: temp
    });

    console.log(this.state.vars);
  }
  handleExport = async () => {
    const nGROKendpoint = 'http://127.0.0.1:8080/export';
    const rawResponse = await fetch(nGROKendpoint,
      { method: 'POST',
        headers: { 'content-type': 'text/plain' }
      }
    );

    var element = document.createElement("a");
    var file = new Blob([await rawResponse.text()], {type: 'text/plain'});
    element.href = URL.createObjectURL(file);
    element.download = "EXPORT_CALC.txt";
    element.click();
  }

  handleImport = async (text) => {

    const nGROKendpoint = 'http://127.0.0.1:8080/import';
    await fetch(nGROKendpoint,
      { method: 'POST',
        headers: { 'content-type': 'text/plain' },
        body: text
      },
    );
    alert("Imported Settings.")
  }

  handleOpenModal = async () => {
    const { isModalOpen } = this.state;
    await this.handleGetVar();
    this.setState({
        isModalOpen: !isModalOpen
    });
  }


  handleChange = async (e,data) => {
    const nGROKendpoint = 'http://127.0.0.1:8080/getresult';
    const rawResponse = await fetch(nGROKendpoint, { method: 'POST',
	headers: { 'content-type': 'text/plain' },
        body: data.value
      }
      );

    const myJSON = JSON.parse(await rawResponse.text())
    this.setState({
      value: myJSON.expression ? myJSON.value : "",
      expression: data.value
    });

    this.checkInput();
    this.checkImport();
    this.checkExport();
    this.checkDelete();
    this.checkClose();
  }

  checkInput = () => {
    const { expression } = this.state;
    if(expression.length !== 0){
      this.setState({
        isVariable: expression[0].match(/[a-z]/i)
      });
    }
    else{
      this.setState({
        isVariable: false
      });
    }
  }

  checkClose = () => {
    const { expression } = this.state;

    if(expression.length >= 4 && expression.includes("exit")){
      this.setState({
        isExiting: expression.includes("exit"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isExiting: false
      });
    }
  }

  checkDelete = () => {
    const {expression} = this.state;

    if(expression.length >= 5 && expression.includes("clear")){
      this.setState({
        isDelete: expression.includes("clear"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isDelete: false
      });
    }
  }

  checkExport = () => {
    const {expression} = this.state;

    if(expression.length >= 6 && expression.includes("export")){
      this.setState({
        isExport: expression.includes("export"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isExport: false
      });
    }
  }

  checkImport = () => {
    const {expression} = this.state;

    if(expression.length >= 6 && expression.includes("import")){
      this.setState({
        isImport: expression.includes("import"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isImport: false
      });
    }
  }

  closeSession = () => {
    alert("I'm a web app! Just close the browser.")
  }

  handleFileChange = (e, results) => {
    results.forEach(result => {
      const [file] = result;
      var fr = new FileReader();

      fr.onload = async (e) => {
        const nGROKendpoint = 'http://127.0.0.1:8080/import';
        await fetch(nGROKendpoint,
          { method: 'POST',
            headers: { 'content-type': 'text/plain' },
            body: e.target.result
          },
        );
        alert("Imported Settings.")
      };

      fr.readAsText(file);
      });
  }

  render() {
    const { isVariable, isDelete, isExport, isImport, isExiting, expression, value, isModalOpen, vars }  = this.state;
    const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    return (
      <div className="App">
        <Modal open={isModalOpen}  size='small'>
          <Header icon='calculator' content='Your Variables' />
          <Modal.Content>
            <List size="huge" className="results" selection>
              {
                vars.map((variable, index) => (
                <List.Item>
                  <List.Content>
                    <List.Header inverted>{alphabet[index]}</List.Header>
                    <p inverted>{variable.value !== "0" ? "expression: " + variable.expression : ""}</p>
                    <p inverted>{variable.value !== "0" ? "value: " + variable.value : ""}</p>
                  </List.Content>
                </List.Item>
              ))}
            </List>
          </Modal.Content>
          <Modal.Actions>
            <Button onClick={this.handleOpenModal} color='red'>
              <Icon name='x' /> Close
            </Button>
          </Modal.Actions>
        </Modal>

        <header className="App-header">
          <div style={{paddingTop: 100, paddingBottom: 300}}>
            <Image onClick={this.handleOpenModal} size='small' centered src={logo} className="App-logo" alt="logo" />
            <p style={{paddingTop: 30, paddingBottom: 30}}>
            <code>Input an algebraic expression.</code>
          </p>
          {
            isVariable &&
            <div style={{paddingBottom: 20}}>
            <Button onClick={this.handleAddVar} size="big" fluid color='yellow'>
              Add Variable
            </Button>
          </div>
          }
          {
            isDelete &&
            <div style={{paddingBottom: 20}}>
            <Button onClick={this.handleDelVar} size="big" fluid color='red'>
              Delete Variable
            </Button>
          </div>
          }
          {
            isExport &&
            <div style={{paddingBottom: 20}}>
            <Button onClick={this.handleExport} size="big" fluid color='green'>
              Export Session
            </Button>
          </div>
          }
          {
            isImport &&
            <div style={{paddingBottom: 20}}>
              <FileReaderInput
                as="text"
                id="my-file-input"
                onChange={this.handleFileChange}>
                <Button size="big" fluid color='blue'>
                  Import Session
                </Button>
              </FileReaderInput>
          </div>
          }
          {
            isExiting &&
            <div style={{paddingBottom: 20}}>
            <Button onClick={this.closeSession} size="big" fluid color='grey'>
              Exit
            </Button>
          </div>
          }
            <Input label='exp' onChange={this.handleChange} fluid size="medium" icon='calculator' placeholder='Numbers go here...' />
            {expression.length === 0 &&
              <div style={{paddingTop: 20}}>
                <List inverted size="small" animated verticalAlign='middle'>
                  <List.Item>
                    <Icon name='plus' size='large' />
                    <List.Content>
                      <List.Header>add expression: f = ...</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='delete' size='large' />
                    <List.Content>
                      <List.Header>clear expression: clear f</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='folder open outline' size='large' />
                    <List.Content>
                      <List.Header>import</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='share' size='large' />
                    <List.Content>
                      <List.Header>export</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='log out' size='large' />
                    <List.Content>
                      <List.Header>exit</List.Header>
                    </List.Content>
                  </List.Item>
                </List>
              </div>
            }
            <Header style={{paddingTop: 80, color: 'white'}} size='huge'>
              {value}
            </Header>

        </div>
        </header>
      </div>
    );
  }
}

export default App;
