using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Input;
using WpfApp.Helpers;

namespace WpfApp.ViewModels
{
  public class MainViewModel : INotifyPropertyChanged
  {
    private string _userInput;

    public string UserInput
    {
      get => _userInput;
      set
      {
        _userInput = value;
        OnPropertyChanged();
      }
    }

    public ICommand RunCommand { get; }

    public MainViewModel()
    {
      RunCommand = new RelayCommand(OnRun);
    }

    private void OnRun()
    {
      MessageBox.Show($"You entered: {UserInput}", "Plugin Executed", MessageBoxButton.OK, MessageBoxImage.Information);
    }

    public event PropertyChangedEventHandler PropertyChanged;

    private void OnPropertyChanged([CallerMemberName] string name = null)
    {
      PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
  }
}